#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {unsigned char* buf; size_t left; size_t offset; size_t len; } ;
struct TYPE_9__ {unsigned char* packet; size_t packet_length; int /*<<< orphan*/  read_ahead; TYPE_2__ rbuf; } ;
struct TYPE_11__ {int mode; int /*<<< orphan*/  rwstate; TYPE_1__ rlayer; int /*<<< orphan*/ * rbio; } ;
typedef  TYPE_2__ SSL3_BUFFER ;
typedef  TYPE_3__ SSL ;

/* Variables and functions */
 int BIO_read (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int SSL3_ALIGN_PAYLOAD ; 
 unsigned char SSL3_RT_APPLICATION_DATA ; 
 size_t SSL3_RT_HEADER_LENGTH ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_SSL3_READ_N ; 
 scalar_t__ SSL_IS_DTLS (TYPE_3__*) ; 
 int SSL_MODE_RELEASE_BUFFERS ; 
 int /*<<< orphan*/  SSL_NOTHING ; 
 int /*<<< orphan*/  SSL_READING ; 
 int /*<<< orphan*/  SSL_R_READ_BIO_NOT_SET ; 
 int /*<<< orphan*/  SSLfatal (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_sys_error () ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  ssl3_release_read_buffer (TYPE_3__*) ; 
 int /*<<< orphan*/  ssl3_setup_read_buffer (TYPE_3__*) ; 

int ssl3_read_n(SSL *s, size_t n, size_t max, int extend, int clearold,
                size_t *readbytes)
{
    /*
     * If extend == 0, obtain new n-byte packet; if extend == 1, increase
     * packet by another n bytes. The packet will be in the sub-array of
     * s->s3->rbuf.buf specified by s->packet and s->packet_length. (If
     * s->rlayer.read_ahead is set, 'max' bytes may be stored in rbuf [plus
     * s->packet_length bytes if extend == 1].)
     * if clearold == 1, move the packet to the start of the buffer; if
     * clearold == 0 then leave any old packets where they were
     */
    size_t len, left, align = 0;
    unsigned char *pkt;
    SSL3_BUFFER *rb;

    if (n == 0)
        return 0;

    rb = &s->rlayer.rbuf;
    if (rb->buf == NULL)
        if (!ssl3_setup_read_buffer(s)) {
            /* SSLfatal() already called */
            return -1;
        }

    left = rb->left;
#if defined(SSL3_ALIGN_PAYLOAD) && SSL3_ALIGN_PAYLOAD!=0
    align = (size_t)rb->buf + SSL3_RT_HEADER_LENGTH;
    align = SSL3_ALIGN_PAYLOAD - 1 - ((align - 1) % SSL3_ALIGN_PAYLOAD);
#endif

    if (!extend) {
        /* start with empty packet ... */
        if (left == 0)
            rb->offset = align;
        else if (align != 0 && left >= SSL3_RT_HEADER_LENGTH) {
            /*
             * check if next packet length is large enough to justify payload
             * alignment...
             */
            pkt = rb->buf + rb->offset;
            if (pkt[0] == SSL3_RT_APPLICATION_DATA
                && (pkt[3] << 8 | pkt[4]) >= 128) {
                /*
                 * Note that even if packet is corrupted and its length field
                 * is insane, we can only be led to wrong decision about
                 * whether memmove will occur or not. Header values has no
                 * effect on memmove arguments and therefore no buffer
                 * overrun can be triggered.
                 */
                memmove(rb->buf + align, pkt, left);
                rb->offset = align;
            }
        }
        s->rlayer.packet = rb->buf + rb->offset;
        s->rlayer.packet_length = 0;
        /* ... now we can act as if 'extend' was set */
    }

    len = s->rlayer.packet_length;
    pkt = rb->buf + align;
    /*
     * Move any available bytes to front of buffer: 'len' bytes already
     * pointed to by 'packet', 'left' extra ones at the end
     */
    if (s->rlayer.packet != pkt && clearold == 1) {
        memmove(pkt, s->rlayer.packet, len + left);
        s->rlayer.packet = pkt;
        rb->offset = len + align;
    }

    /*
     * For DTLS/UDP reads should not span multiple packets because the read
     * operation returns the whole packet at once (as long as it fits into
     * the buffer).
     */
    if (SSL_IS_DTLS(s)) {
        if (left == 0 && extend)
            return 0;
        if (left > 0 && n > left)
            n = left;
    }

    /* if there is enough in the buffer from a previous read, take some */
    if (left >= n) {
        s->rlayer.packet_length += n;
        rb->left = left - n;
        rb->offset += n;
        *readbytes = n;
        return 1;
    }

    /* else we need to read more data */

    if (n > rb->len - rb->offset) {
        /* does not happen */
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL3_READ_N,
                 ERR_R_INTERNAL_ERROR);
        return -1;
    }

    /* We always act like read_ahead is set for DTLS */
    if (!s->rlayer.read_ahead && !SSL_IS_DTLS(s))
        /* ignore max parameter */
        max = n;
    else {
        if (max < n)
            max = n;
        if (max > rb->len - rb->offset)
            max = rb->len - rb->offset;
    }

    while (left < n) {
        size_t bioread = 0;
        int ret;

        /*
         * Now we have len+left bytes at the front of s->s3->rbuf.buf and
         * need to read in more until we have len+n (up to len+max if
         * possible)
         */

        clear_sys_error();
        if (s->rbio != NULL) {
            s->rwstate = SSL_READING;
            /* TODO(size_t): Convert this function */
            ret = BIO_read(s->rbio, pkt + len + left, max - left);
            if (ret >= 0)
                bioread = ret;
        } else {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL3_READ_N,
                     SSL_R_READ_BIO_NOT_SET);
            ret = -1;
        }

        if (ret <= 0) {
            rb->left = left;
            if (s->mode & SSL_MODE_RELEASE_BUFFERS && !SSL_IS_DTLS(s))
                if (len + left == 0)
                    ssl3_release_read_buffer(s);
            return ret;
        }
        left += bioread;
        /*
         * reads should *never* span multiple packets for DTLS because the
         * underlying transport protocol is message oriented as opposed to
         * byte oriented as in the TLS case.
         */
        if (SSL_IS_DTLS(s)) {
            if (n > left)
                n = left;       /* makes the while condition false */
        }
    }

    /* done reading, now the book-keeping */
    rb->offset += n;
    rb->left = left - n;
    s->rlayer.packet_length += n;
    s->rwstate = SSL_NOTHING;
    *readbytes = n;
    return 1;
}
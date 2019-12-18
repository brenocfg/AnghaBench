#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mb_param ;
struct TYPE_30__ {size_t interleave; unsigned char* inp; size_t len; int /*<<< orphan*/ * out; } ;
struct TYPE_27__ {size_t wnum; size_t wpend_tot; size_t* write_sequence; unsigned char const* wpend_buf; int wpend_type; size_t wpend_ret; TYPE_4__* wbuf; } ;
struct TYPE_29__ {scalar_t__ early_data_state; scalar_t__ key_update; int (* handshake_func ) (TYPE_5__*) ;int version; int mode; size_t max_pipelines; TYPE_2__* s3; TYPE_3__ rlayer; int /*<<< orphan*/ * enc_write_ctx; int /*<<< orphan*/  wbio; TYPE_1__* method; int /*<<< orphan*/ * msg_callback; int /*<<< orphan*/ * compress; int /*<<< orphan*/  rwstate; } ;
struct TYPE_28__ {scalar_t__ left; size_t len; scalar_t__ offset; int /*<<< orphan*/ * buf; } ;
struct TYPE_26__ {scalar_t__ empty_fragment_done; scalar_t__ alert_dispatch; } ;
struct TYPE_25__ {int (* ssl_dispatch_alert ) (TYPE_5__*) ;} ;
typedef  TYPE_4__ SSL3_BUFFER ;
typedef  TYPE_5__ SSL ;
typedef  TYPE_6__ EVP_CTRL_TLS1_1_MULTIBLOCK_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_should_retry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_cipher (int /*<<< orphan*/ *) ; 
 void* EVP_CIPHER_CTX_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,TYPE_6__*) ; 
 int EVP_CIPHER_flags (int /*<<< orphan*/ ) ; 
 int EVP_CIPH_FLAG_PIPELINE ; 
 int EVP_CIPH_FLAG_TLS1_1_MULTIBLOCK ; 
 int /*<<< orphan*/  EVP_CTRL_TLS1_1_MULTIBLOCK_AAD ; 
 int /*<<< orphan*/  EVP_CTRL_TLS1_1_MULTIBLOCK_ENCRYPT ; 
 int /*<<< orphan*/  EVP_CTRL_TLS1_1_MULTIBLOCK_MAX_BUFSIZE ; 
 int SSL3_RT_APPLICATION_DATA ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 scalar_t__ SSL_EARLY_DATA_UNAUTH_WRITING ; 
 scalar_t__ SSL_EARLY_DATA_WRITING ; 
 int /*<<< orphan*/  SSL_F_SSL3_WRITE_BYTES ; 
 int /*<<< orphan*/  SSL_IS_DTLS (TYPE_5__*) ; 
 scalar_t__ SSL_KEY_UPDATE_NONE ; 
 size_t SSL_MAX_PIPELINES ; 
 int SSL_MODE_ENABLE_PARTIAL_WRITE ; 
 int SSL_MODE_RELEASE_BUFFERS ; 
 int /*<<< orphan*/  SSL_NOTHING ; 
 int /*<<< orphan*/  SSL_R_BAD_LENGTH ; 
 scalar_t__ SSL_USE_EXPLICIT_IV (TYPE_5__*) ; 
 int /*<<< orphan*/  SSL_WRITE_ETM (TYPE_5__*) ; 
 scalar_t__ SSL_in_init (TYPE_5__*) ; 
 int /*<<< orphan*/  SSLfatal (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int do_ssl3_write (TYPE_5__*,int,unsigned char const*,size_t*,size_t,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  early_data_count_ok (TYPE_5__*,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,size_t*,int) ; 
 int /*<<< orphan*/  ossl_statem_get_in_handshake (TYPE_5__*) ; 
 int /*<<< orphan*/  ossl_statem_set_in_init (TYPE_5__*,int) ; 
 int /*<<< orphan*/  ssl3_release_write_buffer (TYPE_5__*) ; 
 int /*<<< orphan*/  ssl3_setup_write_buffer (TYPE_5__*,int,size_t) ; 
 int ssl3_write_pending (TYPE_5__*,int,unsigned char const*,size_t,size_t*) ; 
 size_t ssl_get_max_send_fragment (TYPE_5__*) ; 
 size_t ssl_get_split_send_fragment (TYPE_5__*) ; 
 int stub1 (TYPE_5__*) ; 
 int stub2 (TYPE_5__*) ; 

int ssl3_write_bytes(SSL *s, int type, const void *buf_, size_t len,
                     size_t *written)
{
    const unsigned char *buf = buf_;
    size_t tot;
    size_t n, max_send_fragment, split_send_fragment, maxpipes;
#if !defined(OPENSSL_NO_MULTIBLOCK) && EVP_CIPH_FLAG_TLS1_1_MULTIBLOCK
    size_t nw;
#endif
    SSL3_BUFFER *wb = &s->rlayer.wbuf[0];
    int i;
    size_t tmpwrit;

    s->rwstate = SSL_NOTHING;
    tot = s->rlayer.wnum;
    /*
     * ensure that if we end up with a smaller value of data to write out
     * than the original len from a write which didn't complete for
     * non-blocking I/O and also somehow ended up avoiding the check for
     * this in ssl3_write_pending/SSL_R_BAD_WRITE_RETRY as it must never be
     * possible to end up with (len-tot) as a large number that will then
     * promptly send beyond the end of the users buffer ... so we trap and
     * report the error in a way the user will notice
     */
    if ((len < s->rlayer.wnum)
        || ((wb->left != 0) && (len < (s->rlayer.wnum + s->rlayer.wpend_tot)))) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL3_WRITE_BYTES,
                 SSL_R_BAD_LENGTH);
        return -1;
    }

    if (s->early_data_state == SSL_EARLY_DATA_WRITING
            && !early_data_count_ok(s, len, 0, 1)) {
        /* SSLfatal() already called */
        return -1;
    }

    s->rlayer.wnum = 0;

    /*
     * If we are supposed to be sending a KeyUpdate then go into init unless we
     * have writes pending - in which case we should finish doing that first.
     */
    if (wb->left == 0 && s->key_update != SSL_KEY_UPDATE_NONE)
        ossl_statem_set_in_init(s, 1);

    /*
     * When writing early data on the server side we could be "in_init" in
     * between receiving the EoED and the CF - but we don't want to handle those
     * messages yet.
     */
    if (SSL_in_init(s) && !ossl_statem_get_in_handshake(s)
            && s->early_data_state != SSL_EARLY_DATA_UNAUTH_WRITING) {
        i = s->handshake_func(s);
        /* SSLfatal() already called */
        if (i < 0)
            return i;
        if (i == 0) {
            return -1;
        }
    }

    /*
     * first check if there is a SSL3_BUFFER still being written out.  This
     * will happen with non blocking IO
     */
    if (wb->left != 0) {
        /* SSLfatal() already called if appropriate */
        i = ssl3_write_pending(s, type, &buf[tot], s->rlayer.wpend_tot,
                               &tmpwrit);
        if (i <= 0) {
            /* XXX should we ssl3_release_write_buffer if i<0? */
            s->rlayer.wnum = tot;
            return i;
        }
        tot += tmpwrit;               /* this might be last fragment */
    }
#if !defined(OPENSSL_NO_MULTIBLOCK) && EVP_CIPH_FLAG_TLS1_1_MULTIBLOCK
    /*
     * Depending on platform multi-block can deliver several *times*
     * better performance. Downside is that it has to allocate
     * jumbo buffer to accommodate up to 8 records, but the
     * compromise is considered worthy.
     */
    if (type == SSL3_RT_APPLICATION_DATA &&
        len >= 4 * (max_send_fragment = ssl_get_max_send_fragment(s)) &&
        s->compress == NULL && s->msg_callback == NULL &&
        !SSL_WRITE_ETM(s) && SSL_USE_EXPLICIT_IV(s) &&
        EVP_CIPHER_flags(EVP_CIPHER_CTX_cipher(s->enc_write_ctx)) &
        EVP_CIPH_FLAG_TLS1_1_MULTIBLOCK) {
        unsigned char aad[13];
        EVP_CTRL_TLS1_1_MULTIBLOCK_PARAM mb_param;
        size_t packlen;
        int packleni;

        /* minimize address aliasing conflicts */
        if ((max_send_fragment & 0xfff) == 0)
            max_send_fragment -= 512;

        if (tot == 0 || wb->buf == NULL) { /* allocate jumbo buffer */
            ssl3_release_write_buffer(s);

            packlen = EVP_CIPHER_CTX_ctrl(s->enc_write_ctx,
                                          EVP_CTRL_TLS1_1_MULTIBLOCK_MAX_BUFSIZE,
                                          (int)max_send_fragment, NULL);

            if (len >= 8 * max_send_fragment)
                packlen *= 8;
            else
                packlen *= 4;

            if (!ssl3_setup_write_buffer(s, 1, packlen)) {
                /* SSLfatal() already called */
                return -1;
            }
        } else if (tot == len) { /* done? */
            /* free jumbo buffer */
            ssl3_release_write_buffer(s);
            *written = tot;
            return 1;
        }

        n = (len - tot);
        for (;;) {
            if (n < 4 * max_send_fragment) {
                /* free jumbo buffer */
                ssl3_release_write_buffer(s);
                break;
            }

            if (s->s3->alert_dispatch) {
                i = s->method->ssl_dispatch_alert(s);
                if (i <= 0) {
                    /* SSLfatal() already called if appropriate */
                    s->rlayer.wnum = tot;
                    return i;
                }
            }

            if (n >= 8 * max_send_fragment)
                nw = max_send_fragment * (mb_param.interleave = 8);
            else
                nw = max_send_fragment * (mb_param.interleave = 4);

            memcpy(aad, s->rlayer.write_sequence, 8);
            aad[8] = type;
            aad[9] = (unsigned char)(s->version >> 8);
            aad[10] = (unsigned char)(s->version);
            aad[11] = 0;
            aad[12] = 0;
            mb_param.out = NULL;
            mb_param.inp = aad;
            mb_param.len = nw;

            packleni = EVP_CIPHER_CTX_ctrl(s->enc_write_ctx,
                                          EVP_CTRL_TLS1_1_MULTIBLOCK_AAD,
                                          sizeof(mb_param), &mb_param);
            packlen = (size_t)packleni;
            if (packleni <= 0 || packlen > wb->len) { /* never happens */
                /* free jumbo buffer */
                ssl3_release_write_buffer(s);
                break;
            }

            mb_param.out = wb->buf;
            mb_param.inp = &buf[tot];
            mb_param.len = nw;

            if (EVP_CIPHER_CTX_ctrl(s->enc_write_ctx,
                                    EVP_CTRL_TLS1_1_MULTIBLOCK_ENCRYPT,
                                    sizeof(mb_param), &mb_param) <= 0)
                return -1;

            s->rlayer.write_sequence[7] += mb_param.interleave;
            if (s->rlayer.write_sequence[7] < mb_param.interleave) {
                int j = 6;
                while (j >= 0 && (++s->rlayer.write_sequence[j--]) == 0) ;
            }

            wb->offset = 0;
            wb->left = packlen;

            s->rlayer.wpend_tot = nw;
            s->rlayer.wpend_buf = &buf[tot];
            s->rlayer.wpend_type = type;
            s->rlayer.wpend_ret = nw;

            i = ssl3_write_pending(s, type, &buf[tot], nw, &tmpwrit);
            if (i <= 0) {
                /* SSLfatal() already called if appropriate */
                if (i < 0 && (!s->wbio || !BIO_should_retry(s->wbio))) {
                    /* free jumbo buffer */
                    ssl3_release_write_buffer(s);
                }
                s->rlayer.wnum = tot;
                return i;
            }
            if (tmpwrit == n) {
                /* free jumbo buffer */
                ssl3_release_write_buffer(s);
                *written = tot + tmpwrit;
                return 1;
            }
            n -= tmpwrit;
            tot += tmpwrit;
        }
    } else
#endif  /* !defined(OPENSSL_NO_MULTIBLOCK) && EVP_CIPH_FLAG_TLS1_1_MULTIBLOCK */
    if (tot == len) {           /* done? */
        if (s->mode & SSL_MODE_RELEASE_BUFFERS && !SSL_IS_DTLS(s))
            ssl3_release_write_buffer(s);

        *written = tot;
        return 1;
    }

    n = (len - tot);

    max_send_fragment = ssl_get_max_send_fragment(s);
    split_send_fragment = ssl_get_split_send_fragment(s);
    /*
     * If max_pipelines is 0 then this means "undefined" and we default to
     * 1 pipeline. Similarly if the cipher does not support pipelined
     * processing then we also only use 1 pipeline, or if we're not using
     * explicit IVs
     */
    maxpipes = s->max_pipelines;
    if (maxpipes > SSL_MAX_PIPELINES) {
        /*
         * We should have prevented this when we set max_pipelines so we
         * shouldn't get here
         */
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL3_WRITE_BYTES,
                 ERR_R_INTERNAL_ERROR);
        return -1;
    }
    if (maxpipes == 0
        || s->enc_write_ctx == NULL
        || !(EVP_CIPHER_flags(EVP_CIPHER_CTX_cipher(s->enc_write_ctx))
             & EVP_CIPH_FLAG_PIPELINE)
        || !SSL_USE_EXPLICIT_IV(s))
        maxpipes = 1;
    if (max_send_fragment == 0 || split_send_fragment == 0
        || split_send_fragment > max_send_fragment) {
        /*
         * We should have prevented this when we set/get the split and max send
         * fragments so we shouldn't get here
         */
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL3_WRITE_BYTES,
                 ERR_R_INTERNAL_ERROR);
        return -1;
    }

    for (;;) {
        size_t pipelens[SSL_MAX_PIPELINES], tmppipelen, remain;
        size_t numpipes, j;

        if (n == 0)
            numpipes = 1;
        else
            numpipes = ((n - 1) / split_send_fragment) + 1;
        if (numpipes > maxpipes)
            numpipes = maxpipes;

        if (n / numpipes >= max_send_fragment) {
            /*
             * We have enough data to completely fill all available
             * pipelines
             */
            for (j = 0; j < numpipes; j++) {
                pipelens[j] = max_send_fragment;
            }
        } else {
            /* We can partially fill all available pipelines */
            tmppipelen = n / numpipes;
            remain = n % numpipes;
            for (j = 0; j < numpipes; j++) {
                pipelens[j] = tmppipelen;
                if (j < remain)
                    pipelens[j]++;
            }
        }

        i = do_ssl3_write(s, type, &(buf[tot]), pipelens, numpipes, 0,
                          &tmpwrit);
        if (i <= 0) {
            /* SSLfatal() already called if appropriate */
            /* XXX should we ssl3_release_write_buffer if i<0? */
            s->rlayer.wnum = tot;
            return i;
        }

        if (tmpwrit == n ||
            (type == SSL3_RT_APPLICATION_DATA &&
             (s->mode & SSL_MODE_ENABLE_PARTIAL_WRITE))) {
            /*
             * next chunk of data should get another prepended empty fragment
             * in ciphersuites with known-IV weakness:
             */
            s->s3->empty_fragment_done = 0;

            if (tmpwrit == n
                    && (s->mode & SSL_MODE_RELEASE_BUFFERS) != 0
                    && !SSL_IS_DTLS(s))
                ssl3_release_write_buffer(s);

            *written = tot + tmpwrit;
            return 1;
        }

        n -= tmpwrit;
        tot += tmpwrit;
    }
}
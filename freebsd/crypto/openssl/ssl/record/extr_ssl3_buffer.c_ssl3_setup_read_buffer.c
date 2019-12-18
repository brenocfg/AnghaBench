#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  rlayer; } ;
struct TYPE_8__ {unsigned char* buf; size_t default_len; size_t len; } ;
typedef  TYPE_1__ SSL3_BUFFER ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 size_t DTLS1_RT_HEADER_LENGTH ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 TYPE_1__* RECORD_LAYER_get_rbuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RECORD_LAYER_set_packet (int /*<<< orphan*/ *,unsigned char*) ; 
 int SSL3_ALIGN_PAYLOAD ; 
 int SSL3_RT_HEADER_LENGTH ; 
 scalar_t__ SSL3_RT_MAX_COMPRESSED_OVERHEAD ; 
 size_t SSL3_RT_MAX_ENCRYPTED_OVERHEAD ; 
 size_t SSL3_RT_MAX_PLAIN_LENGTH ; 
 int /*<<< orphan*/  SSL_AD_NO_ALERT ; 
 int /*<<< orphan*/  SSL_F_SSL3_SETUP_READ_BUFFER ; 
 scalar_t__ SSL_IS_DTLS (TYPE_2__*) ; 
 int /*<<< orphan*/  SSLfatal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ssl_allow_compression (TYPE_2__*) ; 

int ssl3_setup_read_buffer(SSL *s)
{
    unsigned char *p;
    size_t len, align = 0, headerlen;
    SSL3_BUFFER *b;

    b = RECORD_LAYER_get_rbuf(&s->rlayer);

    if (SSL_IS_DTLS(s))
        headerlen = DTLS1_RT_HEADER_LENGTH;
    else
        headerlen = SSL3_RT_HEADER_LENGTH;

#if defined(SSL3_ALIGN_PAYLOAD) && SSL3_ALIGN_PAYLOAD!=0
    align = (-SSL3_RT_HEADER_LENGTH) & (SSL3_ALIGN_PAYLOAD - 1);
#endif

    if (b->buf == NULL) {
        len = SSL3_RT_MAX_PLAIN_LENGTH
            + SSL3_RT_MAX_ENCRYPTED_OVERHEAD + headerlen + align;
#ifndef OPENSSL_NO_COMP
        if (ssl_allow_compression(s))
            len += SSL3_RT_MAX_COMPRESSED_OVERHEAD;
#endif
        if (b->default_len > len)
            len = b->default_len;
        if ((p = OPENSSL_malloc(len)) == NULL) {
            /*
             * We've got a malloc failure, and we're still initialising buffers.
             * We assume we're so doomed that we won't even be able to send an
             * alert.
             */
            SSLfatal(s, SSL_AD_NO_ALERT, SSL_F_SSL3_SETUP_READ_BUFFER,
                     ERR_R_MALLOC_FAILURE);
            return 0;
        }
        b->buf = p;
        b->len = len;
    }

    RECORD_LAYER_set_packet(&s->rlayer, &(b->buf[0]));
    return 1;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int (* handshake_func ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ SSL ;

/* Variables and functions */
 size_t SSL3_RT_MAX_PLAIN_LENGTH ; 
 int /*<<< orphan*/  SSL_F_DTLS1_WRITE_APP_DATA_BYTES ; 
 int /*<<< orphan*/  SSL_R_DTLS_MESSAGE_TOO_BIG ; 
 int /*<<< orphan*/  SSL_R_SSL_HANDSHAKE_FAILURE ; 
 scalar_t__ SSL_in_init (TYPE_1__*) ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dtls1_write_bytes (TYPE_1__*,int,void const*,size_t,size_t*) ; 
 int /*<<< orphan*/  ossl_statem_get_in_handshake (TYPE_1__*) ; 
 int stub1 (TYPE_1__*) ; 

int dtls1_write_app_data_bytes(SSL *s, int type, const void *buf_, size_t len,
                               size_t *written)
{
    int i;

    if (SSL_in_init(s) && !ossl_statem_get_in_handshake(s)) {
        i = s->handshake_func(s);
        if (i < 0)
            return i;
        if (i == 0) {
            SSLerr(SSL_F_DTLS1_WRITE_APP_DATA_BYTES,
                   SSL_R_SSL_HANDSHAKE_FAILURE);
            return -1;
        }
    }

    if (len > SSL3_RT_MAX_PLAIN_LENGTH) {
        SSLerr(SSL_F_DTLS1_WRITE_APP_DATA_BYTES, SSL_R_DTLS_MESSAGE_TOO_BIG);
        return -1;
    }

    return dtls1_write_bytes(s, type, buf_, len, written);
}
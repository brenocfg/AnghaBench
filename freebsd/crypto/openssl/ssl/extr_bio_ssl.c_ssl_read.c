#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t renegotiate_count; size_t byte_count; unsigned long renegotiate_timeout; unsigned long last_time; int /*<<< orphan*/  num_renegotiates; int /*<<< orphan*/ * ssl; } ;
typedef  int /*<<< orphan*/  SSL ;
typedef  TYPE_1__ BIO_SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int BIO_RR_ACCEPT ; 
 int BIO_RR_CONNECT ; 
 int BIO_RR_SSL_X509_LOOKUP ; 
 int /*<<< orphan*/  BIO_clear_retry_flags (int /*<<< orphan*/ *) ; 
 TYPE_1__* BIO_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_retry_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_retry_reason (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BIO_set_retry_special (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_retry_write (int /*<<< orphan*/ *) ; 
#define  SSL_ERROR_NONE 136 
#define  SSL_ERROR_SSL 135 
#define  SSL_ERROR_SYSCALL 134 
#define  SSL_ERROR_WANT_ACCEPT 133 
#define  SSL_ERROR_WANT_CONNECT 132 
#define  SSL_ERROR_WANT_READ 131 
#define  SSL_ERROR_WANT_WRITE 130 
#define  SSL_ERROR_WANT_X509_LOOKUP 129 
#define  SSL_ERROR_ZERO_RETURN 128 
 int SSL_get_error (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_renegotiate (int /*<<< orphan*/ *) ; 
 int ssl_read_internal (int /*<<< orphan*/ *,char*,size_t,size_t*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ssl_read(BIO *b, char *buf, size_t size, size_t *readbytes)
{
    int ret = 1;
    BIO_SSL *sb;
    SSL *ssl;
    int retry_reason = 0;
    int r = 0;

    if (buf == NULL)
        return 0;
    sb = BIO_get_data(b);
    ssl = sb->ssl;

    BIO_clear_retry_flags(b);

    ret = ssl_read_internal(ssl, buf, size, readbytes);

    switch (SSL_get_error(ssl, ret)) {
    case SSL_ERROR_NONE:
        if (sb->renegotiate_count > 0) {
            sb->byte_count += *readbytes;
            if (sb->byte_count > sb->renegotiate_count) {
                sb->byte_count = 0;
                sb->num_renegotiates++;
                SSL_renegotiate(ssl);
                r = 1;
            }
        }
        if ((sb->renegotiate_timeout > 0) && (!r)) {
            unsigned long tm;

            tm = (unsigned long)time(NULL);
            if (tm > sb->last_time + sb->renegotiate_timeout) {
                sb->last_time = tm;
                sb->num_renegotiates++;
                SSL_renegotiate(ssl);
            }
        }

        break;
    case SSL_ERROR_WANT_READ:
        BIO_set_retry_read(b);
        break;
    case SSL_ERROR_WANT_WRITE:
        BIO_set_retry_write(b);
        break;
    case SSL_ERROR_WANT_X509_LOOKUP:
        BIO_set_retry_special(b);
        retry_reason = BIO_RR_SSL_X509_LOOKUP;
        break;
    case SSL_ERROR_WANT_ACCEPT:
        BIO_set_retry_special(b);
        retry_reason = BIO_RR_ACCEPT;
        break;
    case SSL_ERROR_WANT_CONNECT:
        BIO_set_retry_special(b);
        retry_reason = BIO_RR_CONNECT;
        break;
    case SSL_ERROR_SYSCALL:
    case SSL_ERROR_SSL:
    case SSL_ERROR_ZERO_RETURN:
    default:
        break;
    }

    BIO_set_retry_reason(b, retry_reason);

    return ret;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pem_password_cb ;
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_12__ {void* default_passwd_callback_userdata; int /*<<< orphan*/ * default_passwd_callback; } ;
struct TYPE_11__ {void* default_passwd_callback_userdata; int /*<<< orphan*/ * default_passwd_callback; } ;
typedef  TYPE_1__ SSL_CTX ;
typedef  TYPE_2__ SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 scalar_t__ BIO_read_filename (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  BIO_s_file () ; 
 scalar_t__ ERR_GET_LIB (unsigned long) ; 
 scalar_t__ ERR_GET_REASON (unsigned long) ; 
 scalar_t__ ERR_LIB_PEM ; 
 int /*<<< orphan*/  ERR_R_BUF_LIB ; 
 int /*<<< orphan*/  ERR_R_PEM_LIB ; 
 int /*<<< orphan*/  ERR_R_SYS_LIB ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 scalar_t__ ERR_peek_error () ; 
 unsigned long ERR_peek_last_error () ; 
 scalar_t__ PEM_R_NO_START_LINE ; 
 int /*<<< orphan*/ * PEM_read_bio_X509 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/ * PEM_read_bio_X509_AUX (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int SSL_CTX_add0_chain_cert (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int SSL_CTX_clear_chain_certs (TYPE_1__*) ; 
 int SSL_CTX_use_certificate (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_F_USE_CERTIFICATE_CHAIN_FILE ; 
 int SSL_add0_chain_cert (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int SSL_clear_chain_certs (TYPE_2__*) ; 
 int SSL_use_certificate (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int use_certificate_chain_file(SSL_CTX *ctx, SSL *ssl, const char *file)
{
    BIO *in;
    int ret = 0;
    X509 *x = NULL;
    pem_password_cb *passwd_callback;
    void *passwd_callback_userdata;

    ERR_clear_error();          /* clear error stack for
                                 * SSL_CTX_use_certificate() */

    if (ctx != NULL) {
        passwd_callback = ctx->default_passwd_callback;
        passwd_callback_userdata = ctx->default_passwd_callback_userdata;
    } else {
        passwd_callback = ssl->default_passwd_callback;
        passwd_callback_userdata = ssl->default_passwd_callback_userdata;
    }

    in = BIO_new(BIO_s_file());
    if (in == NULL) {
        SSLerr(SSL_F_USE_CERTIFICATE_CHAIN_FILE, ERR_R_BUF_LIB);
        goto end;
    }

    if (BIO_read_filename(in, file) <= 0) {
        SSLerr(SSL_F_USE_CERTIFICATE_CHAIN_FILE, ERR_R_SYS_LIB);
        goto end;
    }

    x = PEM_read_bio_X509_AUX(in, NULL, passwd_callback,
                              passwd_callback_userdata);
    if (x == NULL) {
        SSLerr(SSL_F_USE_CERTIFICATE_CHAIN_FILE, ERR_R_PEM_LIB);
        goto end;
    }

    if (ctx)
        ret = SSL_CTX_use_certificate(ctx, x);
    else
        ret = SSL_use_certificate(ssl, x);

    if (ERR_peek_error() != 0)
        ret = 0;                /* Key/certificate mismatch doesn't imply
                                 * ret==0 ... */
    if (ret) {
        /*
         * If we could set up our certificate, now proceed to the CA
         * certificates.
         */
        X509 *ca;
        int r;
        unsigned long err;

        if (ctx)
            r = SSL_CTX_clear_chain_certs(ctx);
        else
            r = SSL_clear_chain_certs(ssl);

        if (r == 0) {
            ret = 0;
            goto end;
        }

        while ((ca = PEM_read_bio_X509(in, NULL, passwd_callback,
                                       passwd_callback_userdata))
               != NULL) {
            if (ctx)
                r = SSL_CTX_add0_chain_cert(ctx, ca);
            else
                r = SSL_add0_chain_cert(ssl, ca);
            /*
             * Note that we must not free ca if it was successfully added to
             * the chain (while we must free the main certificate, since its
             * reference count is increased by SSL_CTX_use_certificate).
             */
            if (!r) {
                X509_free(ca);
                ret = 0;
                goto end;
            }
        }
        /* When the while loop ends, it's usually just EOF. */
        err = ERR_peek_last_error();
        if (ERR_GET_LIB(err) == ERR_LIB_PEM
            && ERR_GET_REASON(err) == PEM_R_NO_START_LINE)
            ERR_clear_error();
        else
            ret = 0;            /* some real error */
    }

 end:
    X509_free(x);
    BIO_free(in);
    return ret;
}
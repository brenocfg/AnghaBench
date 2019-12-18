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
struct TYPE_7__ {scalar_t__ error; int num_untrusted; int /*<<< orphan*/ * cert; int /*<<< orphan*/ * chain; int /*<<< orphan*/ * dane; } ;
typedef  TYPE_1__ X509_STORE_CTX ;
typedef  int /*<<< orphan*/  SSL_DANE ;

/* Variables and functions */
 scalar_t__ DANETLS_ENABLED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED ; 
 int /*<<< orphan*/  X509_F_X509_VERIFY_CERT ; 
 int /*<<< orphan*/  X509_R_NO_CERT_SET_FOR_US_TO_VERIFY ; 
 int /*<<< orphan*/  X509_V_ERR_EE_KEY_TOO_SMALL ; 
 void* X509_V_ERR_INVALID_CALL ; 
 scalar_t__ X509_V_ERR_OUT_OF_MEM ; 
 scalar_t__ X509_V_ERR_UNSPECIFIED ; 
 scalar_t__ X509_V_OK ; 
 int /*<<< orphan*/  X509_up_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_key_level (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int dane_verify (TYPE_1__*) ; 
 int /*<<< orphan*/ * sk_X509_new_null () ; 
 int /*<<< orphan*/  sk_X509_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify_cb_cert (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int verify_chain (TYPE_1__*) ; 

int X509_verify_cert(X509_STORE_CTX *ctx)
{
    SSL_DANE *dane = ctx->dane;
    int ret;

    if (ctx->cert == NULL) {
        X509err(X509_F_X509_VERIFY_CERT, X509_R_NO_CERT_SET_FOR_US_TO_VERIFY);
        ctx->error = X509_V_ERR_INVALID_CALL;
        return -1;
    }

    if (ctx->chain != NULL) {
        /*
         * This X509_STORE_CTX has already been used to verify a cert. We
         * cannot do another one.
         */
        X509err(X509_F_X509_VERIFY_CERT, ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED);
        ctx->error = X509_V_ERR_INVALID_CALL;
        return -1;
    }

    /*
     * first we make sure the chain we are going to build is present and that
     * the first entry is in place
     */
    if (((ctx->chain = sk_X509_new_null()) == NULL) ||
        (!sk_X509_push(ctx->chain, ctx->cert))) {
        X509err(X509_F_X509_VERIFY_CERT, ERR_R_MALLOC_FAILURE);
        ctx->error = X509_V_ERR_OUT_OF_MEM;
        return -1;
    }
    X509_up_ref(ctx->cert);
    ctx->num_untrusted = 1;

    /* If the peer's public key is too weak, we can stop early. */
    if (!check_key_level(ctx, ctx->cert) &&
        !verify_cb_cert(ctx, ctx->cert, 0, X509_V_ERR_EE_KEY_TOO_SMALL))
        return 0;

    if (DANETLS_ENABLED(dane))
        ret = dane_verify(ctx);
    else
        ret = verify_chain(ctx);

    /*
     * Safety-net.  If we are returning an error, we must also set ctx->error,
     * so that the chain is not considered verified should the error be ignored
     * (e.g. TLS with SSL_VERIFY_NONE).
     */
    if (ret <= 0 && ctx->error == X509_V_OK)
        ctx->error = X509_V_ERR_UNSPECIFIED;
    return ret;
}
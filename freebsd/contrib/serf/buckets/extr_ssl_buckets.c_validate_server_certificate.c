#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* pending_err; void* (* server_cert_callback ) (int /*<<< orphan*/ ,int,TYPE_2__*) ;void* (* server_cert_chain_callback ) (int /*<<< orphan*/ ,int,int,TYPE_2__ const**,int) ;int /*<<< orphan*/  server_cert_userdata; int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ serf_ssl_context_t ;
struct TYPE_7__ {int depth; int /*<<< orphan*/  ssl_cert; } ;
typedef  TYPE_2__ serf_ssl_certificate_t ;
typedef  void* apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  X509_STORE_CTX ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 void* APR_SUCCESS ; 
 void* SERF_ERROR_SSL_CERT_FAILED ; 
 int SERF_SSL_CERT_EXPIRED ; 
 int SERF_SSL_CERT_NOTYETVALID ; 
 int SERF_SSL_CERT_REVOKED ; 
 int SERF_SSL_CERT_SELF_SIGNED ; 
 int SERF_SSL_CERT_UNKNOWNCA ; 
 int SERF_SSL_CERT_UNKNOWN_FAILURE ; 
 TYPE_1__* SSL_get_app_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_get_ex_data_X509_STORE_CTX_idx () ; 
 int STACK_OF (int) ; 
 int X509 ; 
 int X509_STORE_CTX_get_chain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_STORE_CTX_get_current_cert (int /*<<< orphan*/ *) ; 
 int X509_STORE_CTX_get_error (int /*<<< orphan*/ *) ; 
 int X509_STORE_CTX_get_error_depth (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_STORE_CTX_get_ex_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  X509_V_ERR_CERT_HAS_EXPIRED 137 
#define  X509_V_ERR_CERT_NOT_YET_VALID 136 
#define  X509_V_ERR_CERT_REVOKED 135 
#define  X509_V_ERR_CERT_UNTRUSTED 134 
#define  X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT 133 
#define  X509_V_ERR_INVALID_CA 132 
#define  X509_V_ERR_SELF_SIGNED_CERT_IN_CHAIN 131 
#define  X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT 130 
#define  X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY 129 
#define  X509_V_ERR_UNABLE_TO_VERIFY_LEAF_SIGNATURE 128 
 scalar_t__ X509_cmp_current_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_get_notAfter (int) ; 
 int /*<<< orphan*/  X509_get_notBefore (int) ; 
 void* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pool_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_pool_destroy (int /*<<< orphan*/ *) ; 
 int chain ; 
 int server_cert ; 
 int sk_X509_num (int) ; 
 int /*<<< orphan*/  sk_X509_value (int,int) ; 
 void* stub1 (int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 void* stub2 (int /*<<< orphan*/ ,int,int,TYPE_2__ const**,int) ; 
 void* validate_cert_hostname (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
validate_server_certificate(int cert_valid, X509_STORE_CTX *store_ctx)
{
    SSL *ssl;
    serf_ssl_context_t *ctx;
    X509 *server_cert;
    int err, depth;
    int failures = 0;
    apr_status_t status;

    ssl = X509_STORE_CTX_get_ex_data(store_ctx,
                                     SSL_get_ex_data_X509_STORE_CTX_idx());
    ctx = SSL_get_app_data(ssl);

    server_cert = X509_STORE_CTX_get_current_cert(store_ctx);
    depth = X509_STORE_CTX_get_error_depth(store_ctx);

    /* If the certification was found invalid, get the error and convert it to
       something our caller will understand. */
    if (! cert_valid) {
        err = X509_STORE_CTX_get_error(store_ctx);

        switch(err) {
            case X509_V_ERR_CERT_NOT_YET_VALID: 
                    failures |= SERF_SSL_CERT_NOTYETVALID;
                    break;
            case X509_V_ERR_CERT_HAS_EXPIRED:
                    failures |= SERF_SSL_CERT_EXPIRED;
                    break;
            case X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT:
            case X509_V_ERR_SELF_SIGNED_CERT_IN_CHAIN:
                    failures |= SERF_SSL_CERT_SELF_SIGNED;
                    break;
            case X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY:
            case X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT:
            case X509_V_ERR_CERT_UNTRUSTED:
            case X509_V_ERR_INVALID_CA:
            case X509_V_ERR_UNABLE_TO_VERIFY_LEAF_SIGNATURE:
                    failures |= SERF_SSL_CERT_UNKNOWNCA;
                    break;
            case X509_V_ERR_CERT_REVOKED:
                    failures |= SERF_SSL_CERT_REVOKED;
                    break;
            default:
                    failures |= SERF_SSL_CERT_UNKNOWN_FAILURE;
                    break;
        }
    }

    /* Validate hostname */
    status = validate_cert_hostname(server_cert, ctx->pool);
    if (status)
        failures |= SERF_SSL_CERT_UNKNOWN_FAILURE;

    /* Check certificate expiry dates. */
    if (X509_cmp_current_time(X509_get_notBefore(server_cert)) >= 0) {
        failures |= SERF_SSL_CERT_NOTYETVALID;
    }
    else if (X509_cmp_current_time(X509_get_notAfter(server_cert)) <= 0) {
        failures |= SERF_SSL_CERT_EXPIRED;
    }

    if (ctx->server_cert_callback &&
        (depth == 0 || failures)) {
        serf_ssl_certificate_t *cert;
        apr_pool_t *subpool;

        apr_pool_create(&subpool, ctx->pool);

        cert = apr_palloc(subpool, sizeof(serf_ssl_certificate_t));
        cert->ssl_cert = server_cert;
        cert->depth = depth;

        /* Callback for further verification. */
        status = ctx->server_cert_callback(ctx->server_cert_userdata,
                                           failures, cert);
        if (status == APR_SUCCESS)
            cert_valid = 1;
        else {
            /* Even if openssl found the certificate valid, the application
               told us to reject it. */
            cert_valid = 0;
            /* Pass the error back to the caller through the context-run. */
            ctx->pending_err = status;
        }
        apr_pool_destroy(subpool);
    }

    if (ctx->server_cert_chain_callback
        && (depth == 0 || failures)) {
        STACK_OF(X509) *chain;
        const serf_ssl_certificate_t **certs;
        int certs_len;
        apr_pool_t *subpool;

        apr_pool_create(&subpool, ctx->pool);

        /* Borrow the chain to pass to the callback. */
        chain = X509_STORE_CTX_get_chain(store_ctx);

        /* If the chain can't be retrieved, just pass the current
           certificate. */
        /* ### can this actually happen with _get_chain() ?  */
        if (!chain) {
            serf_ssl_certificate_t *cert = apr_palloc(subpool, sizeof(*cert));

            cert->ssl_cert = server_cert;
            cert->depth = depth;

            /* Room for the server_cert and a trailing NULL.  */
            certs = apr_palloc(subpool, sizeof(*certs) * 2);
            certs[0] = cert;

            certs_len = 1;
        } else {
            int i;

            certs_len = sk_X509_num(chain);

            /* Room for all the certs and a trailing NULL.  */
            certs = apr_palloc(subpool, sizeof(*certs) * (certs_len + 1));
            for (i = 0; i < certs_len; ++i) {
                serf_ssl_certificate_t *cert;

                cert = apr_palloc(subpool, sizeof(*cert));
                cert->ssl_cert = sk_X509_value(chain, i);
                cert->depth = i;

                certs[i] = cert;
            }
        }
        certs[certs_len] = NULL;

        /* Callback for further verification. */
        status = ctx->server_cert_chain_callback(ctx->server_cert_userdata,
                                                 failures, depth,
                                                 certs, certs_len);
        if (status == APR_SUCCESS) {
            cert_valid = 1;
        } else {
            /* Even if openssl found the certificate valid, the application
               told us to reject it. */
            cert_valid = 0;
            /* Pass the error back to the caller through the context-run. */
            ctx->pending_err = status;
        }

        apr_pool_destroy(subpool);
    }

    /* Return a specific error if the server certificate is not accepted by
       OpenSSL and the application has not set callbacks to override this. */
    if (!cert_valid &&
        !ctx->server_cert_chain_callback &&
        !ctx->server_cert_callback)
    {
        ctx->pending_err = SERF_ERROR_SSL_CERT_FAILED;
    }
        
    return cert_valid;
}
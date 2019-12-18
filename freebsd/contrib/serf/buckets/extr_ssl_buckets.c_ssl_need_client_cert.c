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
struct TYPE_3__ {char* cert_file_success; char const* cert_path; char* cert_pw_success; scalar_t__ cert_pw_cache_pool; scalar_t__ cert_cache_pool; int /*<<< orphan*/ * cached_cert_pw; int /*<<< orphan*/ * cached_cert; int /*<<< orphan*/  cert_pw_userdata; int /*<<< orphan*/  (* cert_pw_callback ) (int /*<<< orphan*/ ,char const*,char const**) ;int /*<<< orphan*/  pool; int /*<<< orphan*/  cert_userdata; int /*<<< orphan*/  (* cert_callback ) (int /*<<< orphan*/ ,char const**) ;} ;
typedef  TYPE_1__ serf_ssl_context_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  int /*<<< orphan*/  apr_file_t ;
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  PKCS12 ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  BIO_METHOD ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int /*<<< orphan*/  APR_READ ; 
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ *) ; 
 int ERR_GET_FUNC (int) ; 
 int ERR_GET_LIB (int) ; 
 int ERR_GET_REASON (int) ; 
 scalar_t__ ERR_LIB_PKCS12 ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int ERR_get_error () ; 
 scalar_t__ PKCS12_R_MAC_VERIFY_FAILURE ; 
 int /*<<< orphan*/  PKCS12_free (int /*<<< orphan*/ *) ; 
 int PKCS12_parse (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 TYPE_1__* SSL_get_app_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_file_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_file_open (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_pool_cleanup_null ; 
 int /*<<< orphan*/  apr_pool_userdata_setn (char const*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 char* apr_pstrdup (scalar_t__,char const*) ; 
 int /*<<< orphan*/ * bio_meth_file_new () ; 
 int /*<<< orphan*/  bio_meth_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_set_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * d2i_PKCS12_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char const*,char const**) ; 

__attribute__((used)) static int ssl_need_client_cert(SSL *ssl, X509 **cert, EVP_PKEY **pkey)
{
    serf_ssl_context_t *ctx = SSL_get_app_data(ssl);
    apr_status_t status;

    if (ctx->cached_cert) {
        *cert = ctx->cached_cert;
        *pkey = ctx->cached_cert_pw;
        return 1;
    }

    while (ctx->cert_callback) {
        const char *cert_path;
        apr_file_t *cert_file;
        BIO *bio;
        BIO_METHOD *biom;
        PKCS12 *p12;
        int i;
        int retrying_success = 0;

        if (ctx->cert_file_success) {
            status = APR_SUCCESS;
            cert_path = ctx->cert_file_success;
            ctx->cert_file_success = NULL;
            retrying_success = 1;
        } else {
            status = ctx->cert_callback(ctx->cert_userdata, &cert_path);
        }

        if (status || !cert_path) {
            break;
        }

        /* Load the x.509 cert file stored in PKCS12 */
        status = apr_file_open(&cert_file, cert_path, APR_READ, APR_OS_DEFAULT,
                               ctx->pool);

        if (status) {
            continue;
        }

        biom = bio_meth_file_new();
        bio = BIO_new(biom);
        bio_set_data(bio, cert_file);

        ctx->cert_path = cert_path;
        p12 = d2i_PKCS12_bio(bio, NULL);
        apr_file_close(cert_file);

        i = PKCS12_parse(p12, NULL, pkey, cert, NULL);

        if (i == 1) {
            PKCS12_free(p12);
            bio_meth_free(biom);
            ctx->cached_cert = *cert;
            ctx->cached_cert_pw = *pkey;
            if (!retrying_success && ctx->cert_cache_pool) {
                const char *c;

                c = apr_pstrdup(ctx->cert_cache_pool, ctx->cert_path);

                apr_pool_userdata_setn(c, "serf:ssl:cert",
                                       apr_pool_cleanup_null,
                                       ctx->cert_cache_pool);
            }
            return 1;
        }
        else {
            int err = ERR_get_error();
            ERR_clear_error();
            if (ERR_GET_LIB(err) == ERR_LIB_PKCS12 &&
                ERR_GET_REASON(err) == PKCS12_R_MAC_VERIFY_FAILURE) {
                if (ctx->cert_pw_callback) {
                    const char *password;

                    if (ctx->cert_pw_success) {
                        status = APR_SUCCESS;
                        password = ctx->cert_pw_success;
                        ctx->cert_pw_success = NULL;
                    } else {
                        status = ctx->cert_pw_callback(ctx->cert_pw_userdata,
                                                       ctx->cert_path,
                                                       &password);
                    }

                    if (!status && password) {
                        i = PKCS12_parse(p12, password, pkey, cert, NULL);
                        if (i == 1) {
                            PKCS12_free(p12);
                            bio_meth_free(biom);
                            ctx->cached_cert = *cert;
                            ctx->cached_cert_pw = *pkey;
                            if (!retrying_success && ctx->cert_cache_pool) {
                                const char *c;

                                c = apr_pstrdup(ctx->cert_cache_pool,
                                                ctx->cert_path);

                                apr_pool_userdata_setn(c, "serf:ssl:cert",
                                                       apr_pool_cleanup_null,
                                                       ctx->cert_cache_pool);
                            }
                            if (!retrying_success && ctx->cert_pw_cache_pool) {
                                const char *c;

                                c = apr_pstrdup(ctx->cert_pw_cache_pool,
                                                password);

                                apr_pool_userdata_setn(c, "serf:ssl:certpw",
                                                       apr_pool_cleanup_null,
                                                       ctx->cert_pw_cache_pool);
                            }
                            return 1;
                        }
                    }
                }
                PKCS12_free(p12);
                bio_meth_free(biom);
                return 0;
            }
            else {
                printf("OpenSSL cert error: %d %d %d\n", ERR_GET_LIB(err),
                       ERR_GET_FUNC(err),
                       ERR_GET_REASON(err));
                PKCS12_free(p12);
                bio_meth_free(biom);
            }
        }
    }

    return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_14__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  status_type; int /*<<< orphan*/  cookie_hmac_key; TYPE_14__* secure; int /*<<< orphan*/  tick_key_name; } ;
struct TYPE_21__ {int references; int options; int num_tickets; void* recv_max_early_data; scalar_t__ max_early_data; TYPE_2__ ext; void* split_send_fragment; void* max_send_fragment; int /*<<< orphan*/  comp_methods; int /*<<< orphan*/  ex_data; int /*<<< orphan*/ * client_ca_names; int /*<<< orphan*/ * ca_names; int /*<<< orphan*/ * sha1; int /*<<< orphan*/ * md5; int /*<<< orphan*/ * param; int /*<<< orphan*/  cipher_list; int /*<<< orphan*/ * cert; int /*<<< orphan*/  cipher_list_by_id; int /*<<< orphan*/  tls13_ciphersuites; TYPE_3__ const* method; int /*<<< orphan*/ * ctlog_store; int /*<<< orphan*/ * cert_store; int /*<<< orphan*/ * sessions; int /*<<< orphan*/  verify_mode; int /*<<< orphan*/  max_cert_list; int /*<<< orphan*/ * lock; int /*<<< orphan*/  session_timeout; int /*<<< orphan*/  session_cache_size; int /*<<< orphan*/  session_cache_mode; int /*<<< orphan*/  mode; scalar_t__ max_proto_version; scalar_t__ min_proto_version; } ;
struct TYPE_20__ {TYPE_1__* ssl3_enc; int /*<<< orphan*/  (* get_timeout ) () ;} ;
struct TYPE_18__ {int enc_flags; } ;
struct TYPE_17__ {int /*<<< orphan*/  tick_aes_key; int /*<<< orphan*/  tick_hmac_key; } ;
typedef  TYPE_3__ SSL_METHOD ;
typedef  TYPE_4__ SSL_CTX ;
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_EX_INDEX_SSL_CTX ; 
 int /*<<< orphan*/ * CRYPTO_THREAD_lock_new () ; 
 int /*<<< orphan*/  CRYPTO_new_ex_data (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CTLOG_STORE_new () ; 
 int /*<<< orphan*/ * ENGINE_by_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_load_builtin_engines () ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 void* EVP_get_digestbyname (char*) ; 
 int /*<<< orphan*/  OPENSSL_INIT_LOAD_SSL_STRINGS ; 
 int /*<<< orphan*/  OPENSSL_SSL_CLIENT_ENGINE_AUTO ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_4__*) ; 
 int /*<<< orphan*/  OPENSSL_init_ssl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_14__* OPENSSL_secure_zalloc (int) ; 
 TYPE_4__* OPENSSL_zalloc (int) ; 
 scalar_t__ RAND_bytes (int /*<<< orphan*/ ,int) ; 
 scalar_t__ RAND_priv_bytes (int /*<<< orphan*/ ,int) ; 
 void* SSL3_RT_MAX_PLAIN_LENGTH ; 
 int /*<<< orphan*/  SSL_COMP_get_compression_methods () ; 
 int /*<<< orphan*/  SSL_CTX_SRP_CTX_init (TYPE_4__*) ; 
 int /*<<< orphan*/  SSL_CTX_free (TYPE_4__*) ; 
 int /*<<< orphan*/  SSL_CTX_set_ciphersuites (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_client_cert_engine (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_DEFAULT_CIPHER_LIST ; 
 int SSL_ENC_FLAG_DTLS ; 
 int /*<<< orphan*/  SSL_F_SSL_CTX_NEW ; 
 int /*<<< orphan*/  SSL_MAX_CERT_LIST_DEFAULT ; 
 int /*<<< orphan*/  SSL_MODE_AUTO_RETRY ; 
 int SSL_OP_ENABLE_MIDDLEBOX_COMPAT ; 
 int SSL_OP_LEGACY_SERVER_CONNECT ; 
 int SSL_OP_NO_COMPRESSION ; 
 int SSL_OP_NO_TICKET ; 
 int /*<<< orphan*/  SSL_R_LIBRARY_HAS_NO_CIPHERS ; 
 int /*<<< orphan*/  SSL_R_NULL_SSL_METHOD_PASSED ; 
 int /*<<< orphan*/  SSL_R_UNABLE_TO_LOAD_SSL3_MD5_ROUTINES ; 
 int /*<<< orphan*/  SSL_R_UNABLE_TO_LOAD_SSL3_SHA1_ROUTINES ; 
 int /*<<< orphan*/  SSL_R_X509_VERIFICATION_SETUP_PROBLEMS ; 
 int /*<<< orphan*/  SSL_SESSION_CACHE_MAX_SIZE_DEFAULT ; 
 int /*<<< orphan*/  SSL_SESS_CACHE_SERVER ; 
 int /*<<< orphan*/  SSL_VERIFY_NONE ; 
 scalar_t__ SSL_get_ex_data_X509_STORE_CTX_idx () ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLSEXT_STATUSTYPE_nothing ; 
 int /*<<< orphan*/  TLS_DEFAULT_CIPHERSUITES ; 
 int /*<<< orphan*/ * X509_STORE_new () ; 
 int /*<<< orphan*/ * X509_VERIFY_PARAM_new () ; 
 int /*<<< orphan*/  eng_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lh_SSL_SESSION_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sk_SSL_CIPHER_num (int /*<<< orphan*/ ) ; 
 void* sk_X509_NAME_new_null () ; 
 int /*<<< orphan*/ * ssl_cert_new () ; 
 int /*<<< orphan*/  ssl_create_cipher_list (TYPE_3__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssl_ctx_system_config (TYPE_4__*) ; 
 int /*<<< orphan*/  ssl_session_cmp ; 
 int /*<<< orphan*/  ssl_session_hash ; 
 int /*<<< orphan*/  stub1 () ; 

SSL_CTX *SSL_CTX_new(const SSL_METHOD *meth)
{
    SSL_CTX *ret = NULL;

    if (meth == NULL) {
        SSLerr(SSL_F_SSL_CTX_NEW, SSL_R_NULL_SSL_METHOD_PASSED);
        return NULL;
    }

    if (!OPENSSL_init_ssl(OPENSSL_INIT_LOAD_SSL_STRINGS, NULL))
        return NULL;

    if (SSL_get_ex_data_X509_STORE_CTX_idx() < 0) {
        SSLerr(SSL_F_SSL_CTX_NEW, SSL_R_X509_VERIFICATION_SETUP_PROBLEMS);
        goto err;
    }
    ret = OPENSSL_zalloc(sizeof(*ret));
    if (ret == NULL)
        goto err;

    ret->method = meth;
    ret->min_proto_version = 0;
    ret->max_proto_version = 0;
    ret->mode = SSL_MODE_AUTO_RETRY;
    ret->session_cache_mode = SSL_SESS_CACHE_SERVER;
    ret->session_cache_size = SSL_SESSION_CACHE_MAX_SIZE_DEFAULT;
    /* We take the system default. */
    ret->session_timeout = meth->get_timeout();
    ret->references = 1;
    ret->lock = CRYPTO_THREAD_lock_new();
    if (ret->lock == NULL) {
        SSLerr(SSL_F_SSL_CTX_NEW, ERR_R_MALLOC_FAILURE);
        OPENSSL_free(ret);
        return NULL;
    }
    ret->max_cert_list = SSL_MAX_CERT_LIST_DEFAULT;
    ret->verify_mode = SSL_VERIFY_NONE;
    if ((ret->cert = ssl_cert_new()) == NULL)
        goto err;

    ret->sessions = lh_SSL_SESSION_new(ssl_session_hash, ssl_session_cmp);
    if (ret->sessions == NULL)
        goto err;
    ret->cert_store = X509_STORE_new();
    if (ret->cert_store == NULL)
        goto err;
#ifndef OPENSSL_NO_CT
    ret->ctlog_store = CTLOG_STORE_new();
    if (ret->ctlog_store == NULL)
        goto err;
#endif

    if (!SSL_CTX_set_ciphersuites(ret, TLS_DEFAULT_CIPHERSUITES))
        goto err;

    if (!ssl_create_cipher_list(ret->method,
                                ret->tls13_ciphersuites,
                                &ret->cipher_list, &ret->cipher_list_by_id,
                                SSL_DEFAULT_CIPHER_LIST, ret->cert)
        || sk_SSL_CIPHER_num(ret->cipher_list) <= 0) {
        SSLerr(SSL_F_SSL_CTX_NEW, SSL_R_LIBRARY_HAS_NO_CIPHERS);
        goto err2;
    }

    ret->param = X509_VERIFY_PARAM_new();
    if (ret->param == NULL)
        goto err;

    if ((ret->md5 = EVP_get_digestbyname("ssl3-md5")) == NULL) {
        SSLerr(SSL_F_SSL_CTX_NEW, SSL_R_UNABLE_TO_LOAD_SSL3_MD5_ROUTINES);
        goto err2;
    }
    if ((ret->sha1 = EVP_get_digestbyname("ssl3-sha1")) == NULL) {
        SSLerr(SSL_F_SSL_CTX_NEW, SSL_R_UNABLE_TO_LOAD_SSL3_SHA1_ROUTINES);
        goto err2;
    }

    if ((ret->ca_names = sk_X509_NAME_new_null()) == NULL)
        goto err;

    if ((ret->client_ca_names = sk_X509_NAME_new_null()) == NULL)
        goto err;

    if (!CRYPTO_new_ex_data(CRYPTO_EX_INDEX_SSL_CTX, ret, &ret->ex_data))
        goto err;

    if ((ret->ext.secure = OPENSSL_secure_zalloc(sizeof(*ret->ext.secure))) == NULL)
        goto err;

    /* No compression for DTLS */
    if (!(meth->ssl3_enc->enc_flags & SSL_ENC_FLAG_DTLS))
        ret->comp_methods = SSL_COMP_get_compression_methods();

    ret->max_send_fragment = SSL3_RT_MAX_PLAIN_LENGTH;
    ret->split_send_fragment = SSL3_RT_MAX_PLAIN_LENGTH;

    /* Setup RFC5077 ticket keys */
    if ((RAND_bytes(ret->ext.tick_key_name,
                    sizeof(ret->ext.tick_key_name)) <= 0)
        || (RAND_priv_bytes(ret->ext.secure->tick_hmac_key,
                       sizeof(ret->ext.secure->tick_hmac_key)) <= 0)
        || (RAND_priv_bytes(ret->ext.secure->tick_aes_key,
                       sizeof(ret->ext.secure->tick_aes_key)) <= 0))
        ret->options |= SSL_OP_NO_TICKET;

    if (RAND_priv_bytes(ret->ext.cookie_hmac_key,
                   sizeof(ret->ext.cookie_hmac_key)) <= 0)
        goto err;

#ifndef OPENSSL_NO_SRP
    if (!SSL_CTX_SRP_CTX_init(ret))
        goto err;
#endif
#ifndef OPENSSL_NO_ENGINE
# ifdef OPENSSL_SSL_CLIENT_ENGINE_AUTO
#  define eng_strx(x)     #x
#  define eng_str(x)      eng_strx(x)
    /* Use specific client engine automatically... ignore errors */
    {
        ENGINE *eng;
        eng = ENGINE_by_id(eng_str(OPENSSL_SSL_CLIENT_ENGINE_AUTO));
        if (!eng) {
            ERR_clear_error();
            ENGINE_load_builtin_engines();
            eng = ENGINE_by_id(eng_str(OPENSSL_SSL_CLIENT_ENGINE_AUTO));
        }
        if (!eng || !SSL_CTX_set_client_cert_engine(ret, eng))
            ERR_clear_error();
    }
# endif
#endif
    /*
     * Default is to connect to non-RI servers. When RI is more widely
     * deployed might change this.
     */
    ret->options |= SSL_OP_LEGACY_SERVER_CONNECT;
    /*
     * Disable compression by default to prevent CRIME. Applications can
     * re-enable compression by configuring
     * SSL_CTX_clear_options(ctx, SSL_OP_NO_COMPRESSION);
     * or by using the SSL_CONF library. Similarly we also enable TLSv1.3
     * middlebox compatibility by default. This may be disabled by default in
     * a later OpenSSL version.
     */
    ret->options |= SSL_OP_NO_COMPRESSION | SSL_OP_ENABLE_MIDDLEBOX_COMPAT;

    ret->ext.status_type = TLSEXT_STATUSTYPE_nothing;

    /*
     * We cannot usefully set a default max_early_data here (which gets
     * propagated in SSL_new(), for the following reason: setting the
     * SSL field causes tls_construct_stoc_early_data() to tell the
     * client that early data will be accepted when constructing a TLS 1.3
     * session ticket, and the client will accordingly send us early data
     * when using that ticket (if the client has early data to send).
     * However, in order for the early data to actually be consumed by
     * the application, the application must also have calls to
     * SSL_read_early_data(); otherwise we'll just skip past the early data
     * and ignore it.  So, since the application must add calls to
     * SSL_read_early_data(), we also require them to add
     * calls to SSL_CTX_set_max_early_data() in order to use early data,
     * eliminating the bandwidth-wasting early data in the case described
     * above.
     */
    ret->max_early_data = 0;

    /*
     * Default recv_max_early_data is a fully loaded single record. Could be
     * split across multiple records in practice. We set this differently to
     * max_early_data so that, in the default case, we do not advertise any
     * support for early_data, but if a client were to send us some (e.g.
     * because of an old, stale ticket) then we will tolerate it and skip over
     * it.
     */
    ret->recv_max_early_data = SSL3_RT_MAX_PLAIN_LENGTH;

    /* By default we send two session tickets automatically in TLSv1.3 */
    ret->num_tickets = 2;

    ssl_ctx_system_config(ret);

    return ret;
 err:
    SSLerr(SSL_F_SSL_CTX_NEW, ERR_R_MALLOC_FAILURE);
 err2:
    SSL_CTX_free(ret);
    return NULL;
}
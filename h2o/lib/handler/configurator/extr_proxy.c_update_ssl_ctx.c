#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_cache_t ;
typedef  int /*<<< orphan*/  X509_STORE ;
typedef  int /*<<< orphan*/  SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_SESSID_CTX ; 
 int /*<<< orphan*/  H2O_SESSID_CTX_LEN ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_CTX_get_cert_store (int /*<<< orphan*/ *) ; 
 int SSL_CTX_get_verify_mode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_set_cert_store (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_set_session_id_context (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_verify (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_STORE_up_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * create_ssl_ctx () ; 
 int /*<<< orphan*/ * create_ssl_session_cache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_cache_get_capacity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_cache_get_duration (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * h2o_socket_ssl_get_session_cache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_socket_ssl_set_session_cache (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void update_ssl_ctx(SSL_CTX **ctx, X509_STORE *cert_store, int verify_mode, h2o_cache_t **session_cache)
{
    assert(*ctx != NULL);

    /* inherit the properties that weren't specified */
    if (cert_store == NULL)
        cert_store = SSL_CTX_get_cert_store(*ctx);
    X509_STORE_up_ref(cert_store);
    if (verify_mode == -1)
        verify_mode = SSL_CTX_get_verify_mode(*ctx);
    h2o_cache_t *new_session_cache;
    if (session_cache == NULL) {
        h2o_cache_t *current = h2o_socket_ssl_get_session_cache(*ctx);
        new_session_cache =
            current == NULL ? NULL : create_ssl_session_cache(h2o_cache_get_capacity(current), h2o_cache_get_duration(current));
    } else {
        new_session_cache = *session_cache;
    }

    /* free the existing context */
    if (*ctx != NULL)
        SSL_CTX_free(*ctx);

    /* create new ctx */
    *ctx = create_ssl_ctx();
    SSL_CTX_set_session_id_context(*ctx, H2O_SESSID_CTX, H2O_SESSID_CTX_LEN);
    SSL_CTX_set_cert_store(*ctx, cert_store);
    SSL_CTX_set_verify(*ctx, verify_mode, NULL);
    if (new_session_cache != NULL)
        h2o_socket_ssl_set_session_cache(*ctx, new_session_cache);
}
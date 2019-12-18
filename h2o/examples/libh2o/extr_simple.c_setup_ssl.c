#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ssl_ctx; int /*<<< orphan*/ * libmemcached_receiver; } ;

/* Variables and functions */
 int /*<<< orphan*/  OpenSSL_add_all_algorithms () ; 
 int /*<<< orphan*/  SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int SSL_CTX_set_cipher_list (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  SSL_CTX_set_ecdh_auto (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SSL_CTX_set_options (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SSL_CTX_use_PrivateKey_file (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int SSL_CTX_use_certificate_chain_file (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  SSL_FILETYPE_PEM ; 
 int /*<<< orphan*/  SSL_OP_NO_SSLv2 ; 
 int /*<<< orphan*/  SSL_library_init () ; 
 int /*<<< orphan*/  SSL_load_error_strings () ; 
 int /*<<< orphan*/  SSLv23_server_method () ; 
 scalar_t__ USE_MEMCACHED ; 
 TYPE_1__ accept_ctx ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  h2o_accept_setup_memcached_ssl_resumption (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  h2o_http2_alpn_protocols ; 
 int /*<<< orphan*/  h2o_http2_npn_protocols ; 
 int /*<<< orphan*/  h2o_memcached_create_context (char*,int,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  h2o_socket_ssl_async_resumption_setup_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_ssl_register_alpn_protocols (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_ssl_register_npn_protocols (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libmemcached_receiver ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int setup_ssl(const char *cert_file, const char *key_file, const char *ciphers)
{
    SSL_load_error_strings();
    SSL_library_init();
    OpenSSL_add_all_algorithms();

    accept_ctx.ssl_ctx = SSL_CTX_new(SSLv23_server_method());
    SSL_CTX_set_options(accept_ctx.ssl_ctx, SSL_OP_NO_SSLv2);

    if (USE_MEMCACHED) {
        accept_ctx.libmemcached_receiver = &libmemcached_receiver;
        h2o_accept_setup_memcached_ssl_resumption(h2o_memcached_create_context("127.0.0.1", 11211, 0, 1, "h2o:ssl-resumption:"),
                                                  86400);
        h2o_socket_ssl_async_resumption_setup_ctx(accept_ctx.ssl_ctx);
    }

#ifdef SSL_CTX_set_ecdh_auto
    SSL_CTX_set_ecdh_auto(accept_ctx.ssl_ctx, 1);
#endif

    /* load certificate and private key */
    if (SSL_CTX_use_certificate_chain_file(accept_ctx.ssl_ctx, cert_file) != 1) {
        fprintf(stderr, "an error occurred while trying to load server certificate file:%s\n", cert_file);
        return -1;
    }
    if (SSL_CTX_use_PrivateKey_file(accept_ctx.ssl_ctx, key_file, SSL_FILETYPE_PEM) != 1) {
        fprintf(stderr, "an error occurred while trying to load private key file:%s\n", key_file);
        return -1;
    }

    if (SSL_CTX_set_cipher_list(accept_ctx.ssl_ctx, ciphers) != 1) {
        fprintf(stderr, "ciphers could not be set: %s\n", ciphers);
        return -1;
    }

/* setup protocol negotiation methods */
#if H2O_USE_NPN
    h2o_ssl_register_npn_protocols(accept_ctx.ssl_ctx, h2o_http2_npn_protocols);
#endif
#if H2O_USE_ALPN
    h2o_ssl_register_alpn_protocols(accept_ctx.ssl_ctx, h2o_http2_alpn_protocols);
#endif

    return 0;
}
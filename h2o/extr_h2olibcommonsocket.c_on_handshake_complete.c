#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * write; } ;
struct TYPE_14__ {TYPE_4__* ssl; TYPE_2__ _cb; } ;
typedef  TYPE_5__ h2o_socket_t ;
typedef  int /*<<< orphan*/  (* h2o_socket_cb ) (TYPE_5__*,char const*) ;
struct TYPE_10__ {int /*<<< orphan*/  session_cache_key_hash; int /*<<< orphan*/  session_cache_key; int /*<<< orphan*/ * session_cache; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* cb ) (TYPE_5__*,char const*) ;TYPE_1__ client; } ;
struct TYPE_13__ {int record_overhead; TYPE_3__ handshake; int /*<<< orphan*/ * ossl; } ;
typedef  int /*<<< orphan*/  SSL_SESSION ;
typedef  int /*<<< orphan*/  SSL_CIPHER ;

/* Variables and functions */
 int SSL_CIPHER_get_id (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * SSL_get1_session (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_get_current_cipher (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_is_server (int /*<<< orphan*/ *) ; 
#define  TLS1_CK_DHE_RSA_WITH_AES_128_GCM_SHA256 135 
#define  TLS1_CK_DHE_RSA_WITH_AES_256_GCM_SHA384 134 
#define  TLS1_CK_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256 133 
#define  TLS1_CK_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384 132 
#define  TLS1_CK_ECDHE_RSA_WITH_AES_128_GCM_SHA256 131 
#define  TLS1_CK_ECDHE_RSA_WITH_AES_256_GCM_SHA384 130 
#define  TLS1_CK_RSA_WITH_AES_128_GCM_SHA256 129 
#define  TLS1_CK_RSA_WITH_AES_256_GCM_SHA384 128 
 int /*<<< orphan*/  decode_ssl_input (TYPE_5__*) ; 
 int /*<<< orphan*/  h2o_cache_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_iovec_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  h2o_now (int /*<<< orphan*/ ) ; 
 char const* h2o_socket_error_ssl_cert_name_mismatch ; 
 int /*<<< orphan*/  h2o_socket_get_loop (TYPE_5__*) ; 

__attribute__((used)) static void on_handshake_complete(h2o_socket_t *sock, const char *err)
{
    if (err == NULL) {
#if H2O_USE_PICOTLS
        if (sock->ssl->ptls != NULL) {
            sock->ssl->record_overhead = ptls_get_record_overhead(sock->ssl->ptls);
        } else
#endif
        {
            const SSL_CIPHER *cipher = SSL_get_current_cipher(sock->ssl->ossl);
            switch (SSL_CIPHER_get_id(cipher)) {
            case TLS1_CK_RSA_WITH_AES_128_GCM_SHA256:
            case TLS1_CK_DHE_RSA_WITH_AES_128_GCM_SHA256:
            case TLS1_CK_ECDHE_RSA_WITH_AES_128_GCM_SHA256:
            case TLS1_CK_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256:
            case TLS1_CK_RSA_WITH_AES_256_GCM_SHA384:
            case TLS1_CK_DHE_RSA_WITH_AES_256_GCM_SHA384:
            case TLS1_CK_ECDHE_RSA_WITH_AES_256_GCM_SHA384:
            case TLS1_CK_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384:
                sock->ssl->record_overhead = 5 /* header */ + 8 /* record_iv_length (RFC 5288 3) */ + 16 /* tag (RFC 5116 5.1) */;
                break;
#if defined(TLS1_CK_DHE_RSA_CHACHA20_POLY1305)
            case TLS1_CK_DHE_RSA_CHACHA20_POLY1305:
            case TLS1_CK_ECDHE_RSA_CHACHA20_POLY1305:
            case TLS1_CK_ECDHE_ECDSA_CHACHA20_POLY1305:
                sock->ssl->record_overhead = 5 /* header */ + 16 /* tag */;
                break;
#endif
            default:
                sock->ssl->record_overhead = 32; /* sufficiently large number that can hold most payloads */
                break;
            }
        }
    }

    /* set ssl session into the cache */
    if (sock->ssl->ossl != NULL && !SSL_is_server(sock->ssl->ossl) && sock->ssl->handshake.client.session_cache != NULL) {
        if (err == NULL || err == h2o_socket_error_ssl_cert_name_mismatch) {
            SSL_SESSION *session = SSL_get1_session(sock->ssl->ossl);
            h2o_cache_set(sock->ssl->handshake.client.session_cache, h2o_now(h2o_socket_get_loop(sock)),
                          sock->ssl->handshake.client.session_cache_key, sock->ssl->handshake.client.session_cache_key_hash,
                          h2o_iovec_init(session, 1));
        }
    }

    h2o_socket_cb handshake_cb = sock->ssl->handshake.cb;
    sock->_cb.write = NULL;
    sock->ssl->handshake.cb = NULL;
    if (err == NULL)
        decode_ssl_input(sock);
    handshake_cb(sock, err);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* ssl; } ;
typedef  TYPE_4__ h2o_socket_t ;
struct TYPE_6__ {int /*<<< orphan*/  session_cache_key_hash; int /*<<< orphan*/  session_cache_key; int /*<<< orphan*/ * session_cache; } ;
struct TYPE_7__ {TYPE_1__ client; } ;
struct TYPE_8__ {TYPE_2__ handshake; } ;
typedef  int /*<<< orphan*/  SSL_SESSION ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 scalar_t__ SSL_SESSION_is_resumable (int /*<<< orphan*/ *) ; 
 scalar_t__ SSL_get_app_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_is_server (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_cache_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_iovec_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  h2o_now (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_socket_get_loop (TYPE_4__*) ; 

int h2o_socket_ssl_new_session_cb(SSL *s, SSL_SESSION *sess)
{
    h2o_socket_t *sock = (h2o_socket_t *)SSL_get_app_data(s);
    assert(sock != NULL);
    assert(sock->ssl != NULL);

    if (!SSL_is_server(s) && sock->ssl->handshake.client.session_cache != NULL
#if !defined(LIBRESSL_VERSION_NUMBER) && OPENSSL_VERSION_NUMBER >= 0x1010100fL
        && SSL_SESSION_is_resumable(sess)
#endif
    ) {
        h2o_cache_set(sock->ssl->handshake.client.session_cache, h2o_now(h2o_socket_get_loop(sock)),
                      sock->ssl->handshake.client.session_cache_key, sock->ssl->handshake.client.session_cache_key_hash,
                      h2o_iovec_init(sess, 1));
        return 1; /* retain ref count */
    }

    return 0; /* drop ref count */
}
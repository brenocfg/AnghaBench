#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_1__* ssl; } ;
typedef  TYPE_5__ h2o_socket_t ;
struct TYPE_10__ {int state; int /*<<< orphan*/ * session_data; } ;
struct TYPE_9__ {TYPE_3__ async_resumption; } ;
struct TYPE_11__ {TYPE_2__ server; } ;
struct TYPE_8__ {TYPE_4__ handshake; } ;
typedef  int /*<<< orphan*/  SSL_SESSION ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
#define  ASYNC_RESUMPTION_STATE_COMPLETE 129 
#define  ASYNC_RESUMPTION_STATE_RECORD 128 
 int ASYNC_RESUMPTION_STATE_REQUEST_SENT ; 
 TYPE_5__* BIO_get_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_get_rbio (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  h2o_iovec_init (unsigned char const*,int) ; 
 int /*<<< orphan*/  resumption_get_async (TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static SSL_SESSION *on_async_resumption_get(SSL *ssl,
#if !defined(LIBRESSL_VERSION_NUMBER) ? OPENSSL_VERSION_NUMBER >= 0x1010000fL : LIBRESSL_VERSION_NUMBER > 0x2070000f
                                            const
#endif
                                            unsigned char *data,
                                            int len, int *copy)
{
    h2o_socket_t *sock = BIO_get_data(SSL_get_rbio(ssl));

    switch (sock->ssl->handshake.server.async_resumption.state) {
    case ASYNC_RESUMPTION_STATE_RECORD:
        sock->ssl->handshake.server.async_resumption.state = ASYNC_RESUMPTION_STATE_REQUEST_SENT;
        resumption_get_async(sock, h2o_iovec_init(data, len));
        return NULL;
    case ASYNC_RESUMPTION_STATE_COMPLETE:
        *copy = 1;
        return sock->ssl->handshake.server.async_resumption.session_data;
    default:
        assert(!"FIXME");
        return NULL;
    }
}
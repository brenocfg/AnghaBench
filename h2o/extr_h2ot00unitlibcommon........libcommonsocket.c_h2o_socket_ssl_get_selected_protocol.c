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
struct TYPE_3__ {int /*<<< orphan*/ * ssl; } ;
typedef  TYPE_1__ h2o_socket_t ;
typedef  int /*<<< orphan*/  h2o_iovec_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_iovec_init (unsigned char const*,unsigned int) ; 

h2o_iovec_t h2o_socket_ssl_get_selected_protocol(h2o_socket_t *sock)
{
    const unsigned char *data = NULL;
    unsigned len = 0;

    assert(sock->ssl != NULL);

#if H2O_USE_PICOTLS
    if (sock->ssl->ptls != NULL) {
        const char *proto = ptls_get_negotiated_protocol(sock->ssl->ptls);
        return proto != NULL ? h2o_iovec_init(proto, strlen(proto)) : h2o_iovec_init(NULL, 0);
    }
#endif

#if H2O_USE_ALPN
    if (len == 0)
        SSL_get0_alpn_selected(sock->ssl->ossl, &data, &len);
#endif
#if H2O_USE_NPN
    if (len == 0)
        SSL_get0_next_proto_negotiated(sock->ssl->ossl, &data, &len);
#endif

    return h2o_iovec_init(data, len);
}
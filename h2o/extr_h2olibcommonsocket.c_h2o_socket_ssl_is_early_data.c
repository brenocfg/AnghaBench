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

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int h2o_socket_ssl_is_early_data(h2o_socket_t *sock)
{
    assert(sock->ssl != NULL);

#if H2O_USE_PICOTLS
    if (sock->ssl->ptls != NULL && !ptls_handshake_is_complete(sock->ssl->ptls))
        return 1;
#endif
    return 0;
}
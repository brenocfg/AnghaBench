#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* ssl; } ;
typedef  TYPE_2__ h2o_socket_t ;
struct TYPE_4__ {int /*<<< orphan*/ * ossl; int /*<<< orphan*/ * ptls; } ;

/* Variables and functions */
 char const* SSL_get_version (int /*<<< orphan*/ *) ; 

const char *h2o_socket_get_ssl_protocol_version(h2o_socket_t *sock)
{
    if (sock->ssl != NULL) {
        if (sock->ssl->ptls != NULL)
            return "TLSv1.3";
        if (sock->ssl->ossl != NULL)
            return SSL_get_version(sock->ssl->ossl);
    }
    return NULL;
}
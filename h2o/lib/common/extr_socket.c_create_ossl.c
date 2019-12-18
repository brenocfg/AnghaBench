#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* ssl; } ;
typedef  TYPE_2__ h2o_socket_t ;
struct TYPE_6__ {int /*<<< orphan*/  ossl; int /*<<< orphan*/  ssl_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_app_data (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  setup_bio (TYPE_2__*) ; 

__attribute__((used)) static void create_ossl(h2o_socket_t *sock)
{
    sock->ssl->ossl = SSL_new(sock->ssl->ssl_ctx);
    /* set app data to be used in h2o_socket_ssl_new_session_cb */
    SSL_set_app_data(sock->ssl->ossl, sock);
    setup_bio(sock);
}
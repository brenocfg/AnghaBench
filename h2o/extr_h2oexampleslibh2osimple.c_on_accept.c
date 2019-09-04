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
typedef  int /*<<< orphan*/  h2o_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  accept_ctx ; 
 int /*<<< orphan*/  h2o_accept (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * h2o_evloop_socket_accept (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void on_accept(h2o_socket_t *listener, const char *err)
{
    h2o_socket_t *sock;

    if (err != NULL) {
        return;
    }

    if ((sock = h2o_evloop_socket_accept(listener)) == NULL)
        return;
    h2o_accept(&accept_ctx, sock);
}
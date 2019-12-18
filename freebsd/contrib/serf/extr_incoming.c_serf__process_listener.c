#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  accept_baton; int /*<<< orphan*/  ctx; scalar_t__ (* accept_func ) (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  skt; int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ serf_listener_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_socket_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  apr_pool_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_pool_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ apr_socket_accept (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

apr_status_t serf__process_listener(serf_listener_t *l)
{
    apr_status_t rv;
    apr_socket_t *in;
    apr_pool_t *p;
    /* THIS IS NOT OPTIMAL */
    apr_pool_create(&p, l->pool);

    rv = apr_socket_accept(&in, l->skt, p);

    if (rv) {
        apr_pool_destroy(p);
        return rv;
    }

    rv = l->accept_func(l->ctx, l, l->accept_baton, in, p);

    if (rv) {
        apr_pool_destroy(p);
        return rv;
    }

    return rv;
}
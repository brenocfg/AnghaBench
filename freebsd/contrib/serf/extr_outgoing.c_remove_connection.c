#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  pollset_baton; int /*<<< orphan*/  (* pollset_rm ) (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ serf_context_t ;
struct TYPE_10__ {int /*<<< orphan*/  baton; int /*<<< orphan*/  reqevents; int /*<<< orphan*/  skt; } ;
typedef  TYPE_3__ serf_connection_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
struct TYPE_8__ {int /*<<< orphan*/  s; } ;
struct TYPE_11__ {int /*<<< orphan*/  reqevents; TYPE_1__ desc; int /*<<< orphan*/  desc_type; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ apr_pollfd_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_POLL_SOCKET ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static apr_status_t remove_connection(serf_context_t *ctx,
                                      serf_connection_t *conn)
{
    apr_pollfd_t desc = { 0 };

    desc.desc_type = APR_POLL_SOCKET;
    desc.desc.s = conn->skt;
    desc.reqevents = conn->reqevents;

    return ctx->pollset_rm(ctx->pollset_baton,
                           &desc, &conn->baton);
}
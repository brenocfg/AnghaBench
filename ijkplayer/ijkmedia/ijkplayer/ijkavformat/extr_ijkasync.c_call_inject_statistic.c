#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  statistic ;
struct TYPE_6__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_8__ {int size; scalar_t__ buf_capacity; int /*<<< orphan*/  buf_backwards; int /*<<< orphan*/  buf_forwards; int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {scalar_t__ app_ctx; scalar_t__ backwards_capacity; scalar_t__ forwards_capacity; int /*<<< orphan*/  ring; } ;
typedef  TYPE_2__ Context ;
typedef  TYPE_3__ AVAppAsyncStatistic ;

/* Variables and functions */
 int /*<<< orphan*/  av_application_on_async_statistic (scalar_t__,TYPE_3__*) ; 
 int /*<<< orphan*/  ring_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ring_size_of_read_back (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void call_inject_statistic(URLContext *h)
{
    Context *c = h->priv_data;

    if (c->app_ctx) {
        AVAppAsyncStatistic statistic = {0};
        statistic.size = sizeof(statistic);
        statistic.buf_forwards  = ring_size(&c->ring);
        statistic.buf_backwards = ring_size_of_read_back(&c->ring);
        statistic.buf_capacity  = c->forwards_capacity + c->backwards_capacity;
        av_application_on_async_statistic(c->app_ctx, &statistic);
    }
}
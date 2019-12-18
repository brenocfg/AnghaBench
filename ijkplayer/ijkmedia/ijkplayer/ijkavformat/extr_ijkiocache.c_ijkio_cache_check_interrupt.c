#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int abort_request; TYPE_1__* ijkio_interrupt_callback; } ;
struct TYPE_6__ {TYPE_3__* priv_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  opaque; scalar_t__ (* callback ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ IjkURLContext ;
typedef  TYPE_3__ IjkIOCacheContext ;

/* Variables and functions */
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ijkio_cache_check_interrupt(IjkURLContext *h)
{
    IjkIOCacheContext *c = h->priv_data;
    if (!c)
        return 1;

    if (c->abort_request)
        return 1;

    if (c->ijkio_interrupt_callback && c->ijkio_interrupt_callback->callback &&
                    c->ijkio_interrupt_callback->callback(c->ijkio_interrupt_callback->opaque)) {
        c->abort_request = 1;
    }

    if (c->abort_request)
        return 1;

    return c->abort_request;
}
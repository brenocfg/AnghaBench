#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_4__ {int abort_request; int /*<<< orphan*/  interrupt_callback; } ;
typedef  TYPE_2__ Context ;

/* Variables and functions */
 scalar_t__ ff_check_interrupt (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int async_check_interrupt(void *arg)
{
    URLContext *h   = arg;
    Context    *c   = h->priv_data;

    if (c->abort_request)
        return 1;

    if (ff_check_interrupt(&c->interrupt_callback))
        c->abort_request = 1;

    return c->abort_request;
}
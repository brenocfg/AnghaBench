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
struct TYPE_6__ {int /*<<< orphan*/  rxs; } ;
struct TYPE_7__ {TYPE_1__ hopt; } ;
typedef  TYPE_2__ ct_chan_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_LINE ; 
 int /*<<< orphan*/  CLK_RXS_DPLL_INT ; 
 scalar_t__ ct_get_baud (TYPE_2__*) ; 
 int /*<<< orphan*/  ct_update_chan (TYPE_2__*) ; 

void ct_set_dpll (ct_chan_t *c, int on)
{
	if (on && ct_get_baud (c))
		c->hopt.rxs = CLK_RXS_DPLL_INT;
	else
		c->hopt.rxs = CLK_LINE;
	ct_update_chan (c);
}
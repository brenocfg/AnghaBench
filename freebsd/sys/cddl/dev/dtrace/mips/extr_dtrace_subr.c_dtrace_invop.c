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
struct trapframe {int dummy; } ;
struct TYPE_3__ {int (* dtih_func ) (uintptr_t,struct trapframe*,uintptr_t) ;struct TYPE_3__* dtih_next; } ;
typedef  TYPE_1__ dtrace_invop_hdlr_t ;

/* Variables and functions */
 TYPE_1__* dtrace_invop_hdlr ; 
 int stub1 (uintptr_t,struct trapframe*,uintptr_t) ; 

int
dtrace_invop(uintptr_t addr, struct trapframe *stack, uintptr_t eax)
{
	dtrace_invop_hdlr_t *hdlr;
	int rval;

	for (hdlr = dtrace_invop_hdlr; hdlr != NULL; hdlr = hdlr->dtih_next)
		if ((rval = hdlr->dtih_func(addr, stack, eax)) != 0)
			return (rval);

	return (0);
}
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
struct tcb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_SET_TP ; 
 scalar_t__ ARM_TP_ADDRESS ; 
 int /*<<< orphan*/  sysarch (int /*<<< orphan*/ ,void*) ; 

void
_set_tp(void *tp)
{

#ifdef ARM_TP_ADDRESS
	*((struct tcb **)ARM_TP_ADDRESS) = tp;
#else
	sysarch(ARM_SET_TP, tp);
#endif
}
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
typedef  scalar_t__ t_Error ;
struct resource {int dummy; } ;
struct TYPE_3__ {unsigned int cpu; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ E_OK ; 
 int /*<<< orphan*/  XX_Dispatch ; 
 int /*<<< orphan*/  XX_INTR_FLAG_PREALLOCATED ; 
 TYPE_1__* XX_IntrInfo ; 
 scalar_t__ XX_SetIntr (uintptr_t,int /*<<< orphan*/ ,TYPE_1__*) ; 
 unsigned int rman_get_start (struct resource*) ; 

t_Error
XX_PreallocAndBindIntr(uintptr_t irq, unsigned int cpu)
{
	struct resource *r;
	unsigned int inum;
	t_Error error;

	r = (struct resource *)irq;
	inum = rman_get_start(r);

	error = XX_SetIntr(irq, XX_Dispatch, &XX_IntrInfo[inum]);
	if (error != 0)
		return (error);

	XX_IntrInfo[inum].flags = XX_INTR_FLAG_PREALLOCATED;
	XX_IntrInfo[inum].cpu = cpu;

	return (E_OK);
}
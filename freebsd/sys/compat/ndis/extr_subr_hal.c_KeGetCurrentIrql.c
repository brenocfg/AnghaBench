#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {size_t td_oncpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISPATCH_LEVEL ; 
 int /*<<< orphan*/  PASSIVE_LEVEL ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/ * disp_lock ; 
 scalar_t__ mtx_owned (int /*<<< orphan*/ *) ; 

uint8_t
KeGetCurrentIrql()
{
	if (mtx_owned(&disp_lock[curthread->td_oncpu]))
		return (DISPATCH_LEVEL);
	return (PASSIVE_LEVEL);
}
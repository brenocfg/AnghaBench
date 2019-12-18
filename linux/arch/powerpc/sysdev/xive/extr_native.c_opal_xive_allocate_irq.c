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
typedef  int /*<<< orphan*/  u32 ;
typedef  int s64 ;

/* Variables and functions */
 int OPAL_RESOURCE ; 
 int opal_xive_allocate_irq_raw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static s64 opal_xive_allocate_irq(u32 chip_id)
{
	s64 irq = opal_xive_allocate_irq_raw(chip_id);

	/*
	 * Old versions of skiboot can incorrectly return 0xffffffff to
	 * indicate no space, fix it up here.
	 */
	return irq == 0xffffffff ? OPAL_RESOURCE : irq;
}
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

/* Variables and functions */
 int /*<<< orphan*/  slb_flush_and_restore_bolted () ; 

void slb_vmalloc_update(void)
{
	/*
	 * vmalloc is not bolted, so just have to flush non-bolted.
	 */
	slb_flush_and_restore_bolted();
}
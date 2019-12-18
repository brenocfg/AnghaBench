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
 int /*<<< orphan*/  beripic_send_ipi (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mips_sync () ; 
 int /*<<< orphan*/ * picmap ; 

void
platform_ipi_send(int cpuid)
{

	mips_sync();	/* Ordering, liveness. */

	beripic_send_ipi(picmap[cpuid], cpuid);
}
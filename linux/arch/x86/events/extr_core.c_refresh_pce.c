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
struct TYPE_2__ {int /*<<< orphan*/  loaded_mm; } ;

/* Variables and functions */
 TYPE_1__ cpu_tlbstate ; 
 int /*<<< orphan*/  load_mm_cr4_irqsoff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void refresh_pce(void *ignored)
{
	load_mm_cr4_irqsoff(this_cpu_read(cpu_tlbstate.loaded_mm));
}
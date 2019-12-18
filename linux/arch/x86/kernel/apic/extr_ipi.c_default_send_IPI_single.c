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
struct TYPE_2__ {int /*<<< orphan*/  (* send_IPI_mask ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 TYPE_1__* apic ; 
 int /*<<< orphan*/  cpumask_of (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

void default_send_IPI_single(int cpu, int vector)
{
	apic->send_IPI_mask(cpumask_of(cpu), vector);
}
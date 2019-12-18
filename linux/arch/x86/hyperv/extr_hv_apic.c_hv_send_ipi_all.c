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
struct TYPE_2__ {int /*<<< orphan*/  (* send_IPI_all ) (int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __send_ipi_mask (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 TYPE_1__ orig_apic ; 
 int /*<<< orphan*/  stub1 (int) ; 

__attribute__((used)) static void hv_send_ipi_all(int vector)
{
	if (!__send_ipi_mask(cpu_online_mask, vector))
		orig_apic.send_IPI_all(vector);
}
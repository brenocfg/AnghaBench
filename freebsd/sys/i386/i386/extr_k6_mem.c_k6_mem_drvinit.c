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
struct TYPE_2__ {int /*<<< orphan*/ * mr_op; } ;

/* Variables and functions */
 scalar_t__ CPU_VENDOR_AMD ; 
 int cpu_id ; 
 scalar_t__ cpu_vendor_id ; 
 int /*<<< orphan*/  k6_mrops ; 
 TYPE_1__ mem_range_softc ; 

__attribute__((used)) static void
k6_mem_drvinit(void *unused)
{

	if (cpu_vendor_id != CPU_VENDOR_AMD)
		return;
	if ((cpu_id & 0xf00) != 0x500)
		return;
	if ((cpu_id & 0xf0) < 0x80 ||
	    ((cpu_id & 0xf0) == 0x80 && (cpu_id & 0xf) <= 0x7))
		return;
	mem_range_softc.mr_op = &k6_mrops;
}
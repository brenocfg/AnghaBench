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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ num_cpus; } ;
typedef  TYPE_1__ ocs_cpuinfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_get_cpuinfo (TYPE_1__*) ; 

uint32_t
ocs_get_num_cpus(void)
{
	static ocs_cpuinfo_t cpuinfo;

	if (cpuinfo.num_cpus == 0) {
		ocs_get_cpuinfo(&cpuinfo);
	}
	return cpuinfo.num_cpus;
}
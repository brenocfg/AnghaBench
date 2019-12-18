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
typedef  int uint32_t ;
typedef  int u_long ;
typedef  int /*<<< orphan*/  physmem ;

/* Variables and functions */
 int CTL_HW ; 
 int HW_PHYSMEM ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int SNMP_ERR_GENERR ; 
 int SNMP_ERR_NOERROR ; 
 int UINT32_MAX ; 
 int phys_mem_size ; 
 int sysctl (int*,int,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
OS_getMemorySize(uint32_t *ms)
{

	if (phys_mem_size == 0) {
		int mib[2] = { CTL_HW, HW_PHYSMEM };
		u_long physmem;
		size_t len = sizeof(physmem);

		if (sysctl(mib, 2, &physmem, &len, NULL, 0) == -1) {
			syslog(LOG_ERR,
			    "sysctl({ CTL_HW, HW_PHYSMEM }) failed: %m");
			return (SNMP_ERR_GENERR);
		}

		phys_mem_size = physmem / 1024;
	}

	if (phys_mem_size > UINT32_MAX)
		*ms = UINT32_MAX;
	else
		*ms = phys_mem_size;
	return (SNMP_ERR_NOERROR);
}
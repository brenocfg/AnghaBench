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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  pcell_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int PSCI_RETVAL_SUCCESS ; 
 scalar_t__ mp_ncpus ; 
 scalar_t__ mpentry ; 
 int /*<<< orphan*/  pmap_kextract (int /*<<< orphan*/ ) ; 
 int psci_cpu_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ running_cpus ; 

__attribute__((used)) static boolean_t
virt_start_ap(u_int id, phandle_t node, u_int addr_cells, pcell_t *reg)
{
	int err;

	if (running_cpus >= mp_ncpus)
		return (false);
	running_cpus++;

	err = psci_cpu_on(*reg, pmap_kextract((vm_offset_t)mpentry), id);

	if (err != PSCI_RETVAL_SUCCESS)
		return (false);

	return (true);
}
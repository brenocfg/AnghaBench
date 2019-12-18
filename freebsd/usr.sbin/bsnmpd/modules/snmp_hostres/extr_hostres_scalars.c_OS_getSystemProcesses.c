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

/* Variables and functions */
 int /*<<< orphan*/  KERN_PROC_PROC ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int SNMP_ERR_GENERR ; 
 int SNMP_ERR_NOERROR ; 
 int /*<<< orphan*/ * hr_kd ; 
 int /*<<< orphan*/ * kvm_getprocs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
OS_getSystemProcesses(uint32_t *proc_count)
{
	int pc;

	if (hr_kd == NULL)
		return (SNMP_ERR_GENERR);

	if (kvm_getprocs(hr_kd, KERN_PROC_PROC, 0, &pc) == NULL) {
		syslog(LOG_ERR, "kvm_getprocs failed: %m");
		return (SNMP_ERR_GENERR);
	}

	*proc_count = pc;
	return (SNMP_ERR_NOERROR);
}
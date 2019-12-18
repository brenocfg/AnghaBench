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
typedef  int /*<<< orphan*/  mp ;

/* Variables and functions */
 int CTL_KERN ; 
 int KERN_MAXPROC ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int SNMP_ERR_GENERR ; 
 int SNMP_ERR_NOERROR ; 
 int max_proc ; 
 int sysctl (int*,int,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
OS_getSystemMaxProcesses(uint32_t *mproc)
{

	if (max_proc == 0) {
		int mib[2] = { CTL_KERN, KERN_MAXPROC };
		int mp;
		size_t len = sizeof(mp);

		if (sysctl(mib, 2, &mp, &len, NULL, 0) == -1) {
			syslog(LOG_ERR, "sysctl KERN_MAXPROC failed: %m");
			return (SNMP_ERR_GENERR);
		}
		max_proc = mp;
	}

	*mproc = max_proc;
	return (SNMP_ERR_NOERROR);
}
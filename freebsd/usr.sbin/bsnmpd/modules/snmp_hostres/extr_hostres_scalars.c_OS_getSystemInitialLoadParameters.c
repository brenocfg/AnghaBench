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
typedef  char u_char ;

/* Variables and functions */
 int CTL_KERN ; 
 int /*<<< orphan*/  HRDBG (char*,char*) ; 
 int KERN_BOOTFILE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int SNMP_ERR_GENERR ; 
 int SNMP_ERR_NOERROR ; 
 char* boot_line ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 scalar_t__ sysctl (int*,int,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

int
OS_getSystemInitialLoadParameters(u_char **params)
{

	if (boot_line == NULL) {
		int mib[2] = { CTL_KERN, KERN_BOOTFILE };
		char *buf;
		size_t buf_len = 0;

		/* get the needed buffer len */
		if (sysctl(mib, 2, NULL, &buf_len, NULL, 0) != 0) {
			syslog(LOG_ERR,
			    "sysctl({CTL_KERN,KERN_BOOTFILE}) failed: %m");
			return (SNMP_ERR_GENERR);
		}

		if ((buf = malloc(buf_len)) == NULL) {
			syslog(LOG_ERR, "malloc failed");
			return (SNMP_ERR_GENERR);
		}
		if (sysctl(mib, 2, buf, &buf_len, NULL, 0)) {
			syslog(LOG_ERR,
			    "sysctl({CTL_KERN,KERN_BOOTFILE}) failed: %m");
			free(buf);
			return (SNMP_ERR_GENERR);
		}

		boot_line = buf;
		HRDBG("kernel boot file: %s", boot_line);
	}

	*params = boot_line;
	return (SNMP_ERR_NOERROR);
}
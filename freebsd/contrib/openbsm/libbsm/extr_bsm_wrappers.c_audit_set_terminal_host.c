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
 int CTL_KERN ; 
 int KERN_HOSTID ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  errno ; 
 int kAUBadParamErr ; 
 int kAUNoErr ; 
 int kAUSysctlErr ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ sysctl (int*,int,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int
audit_set_terminal_host(uint32_t *m)
{

#ifdef KERN_HOSTID
	int name[2] = { CTL_KERN, KERN_HOSTID };
	size_t len;

	if (m == NULL)
		return (kAUBadParamErr);
	*m = 0;
	len = sizeof(*m);
	if (sysctl(name, 2, m, &len, NULL, 0) != 0) {
		syslog(LOG_ERR, "sysctl() failed (%s)", strerror(errno));
		return (kAUSysctlErr);
	}
	return (kAUNoErr);
#else
	*m = -1;
	return (kAUNoErr);
#endif
}
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
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  mibvar ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 char** socktype ; 
 scalar_t__ sysctlbyname (char*,char*,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_warn (char*,char*) ; 
 int /*<<< orphan*/  xo_warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pcblist_sysctl(int type, char **bufp)
{
	char 	*buf;
	size_t	len;
	char mibvar[sizeof "net.local.seqpacket.pcblist"];

	snprintf(mibvar, sizeof(mibvar), "net.local.%s.pcblist", socktype[type]);

	len = 0;
	if (sysctlbyname(mibvar, 0, &len, 0, 0) < 0) {
		if (errno != ENOENT)
			xo_warn("sysctl: %s", mibvar);
		return (-1);
	}
	if ((buf = malloc(len)) == NULL) {
		xo_warnx("malloc %lu bytes", (u_long)len);
		return (-2);
	}
	if (sysctlbyname(mibvar, buf, &len, 0, 0) < 0) {
		xo_warn("sysctl: %s", mibvar);
		free(buf);
		return (-2);
	}
	*bufp = buf;
	return (0);
}
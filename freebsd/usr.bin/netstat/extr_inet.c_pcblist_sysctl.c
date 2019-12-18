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

/* Variables and functions */
 scalar_t__ ENOENT ; 
#define  IPPROTO_DIVERT 130 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 scalar_t__ sysctlbyname (char const*,char*,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_warn (char*,char const*) ; 
 int /*<<< orphan*/  xo_warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pcblist_sysctl(int proto, const char *name, char **bufp)
{
	const char *mibvar;
	char *buf;
	size_t len;

	switch (proto) {
	case IPPROTO_TCP:
		mibvar = "net.inet.tcp.pcblist";
		break;
	case IPPROTO_UDP:
		mibvar = "net.inet.udp.pcblist";
		break;
	case IPPROTO_DIVERT:
		mibvar = "net.inet.divert.pcblist";
		break;
	default:
		mibvar = "net.inet.raw.pcblist";
		break;
	}
	if (strncmp(name, "sdp", 3) == 0)
		mibvar = "net.inet.sdp.pcblist";
	len = 0;
	if (sysctlbyname(mibvar, 0, &len, 0, 0) < 0) {
		if (errno != ENOENT)
			xo_warn("sysctl: %s", mibvar);
		return (0);
	}
	if ((buf = malloc(len)) == NULL) {
		xo_warnx("malloc %lu bytes", (u_long)len);
		return (0);
	}
	if (sysctlbyname(mibvar, buf, &len, 0, 0) < 0) {
		xo_warn("sysctl: %s", mibvar);
		free(buf);
		return (0);
	}
	*bufp = buf;
	return (1);
}
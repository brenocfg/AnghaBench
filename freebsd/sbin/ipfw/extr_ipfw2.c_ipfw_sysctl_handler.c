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
typedef  int /*<<< orphan*/  which ;

/* Variables and functions */
 scalar_t__ _substrcmp (char*,char*) ; 
 int /*<<< orphan*/  altq_set_enabled (int) ; 
 int /*<<< orphan*/  sysctlbyname (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

void
ipfw_sysctl_handler(char *av[], int which)
{
	av++;

	if (av[0] == NULL) {
		warnx("missing keyword to enable/disable\n");
	} else if (_substrcmp(*av, "firewall") == 0) {
		sysctlbyname("net.inet.ip.fw.enable", NULL, 0,
		    &which, sizeof(which));
		sysctlbyname("net.inet6.ip6.fw.enable", NULL, 0,
		    &which, sizeof(which));
	} else if (_substrcmp(*av, "one_pass") == 0) {
		sysctlbyname("net.inet.ip.fw.one_pass", NULL, 0,
		    &which, sizeof(which));
	} else if (_substrcmp(*av, "debug") == 0) {
		sysctlbyname("net.inet.ip.fw.debug", NULL, 0,
		    &which, sizeof(which));
	} else if (_substrcmp(*av, "verbose") == 0) {
		sysctlbyname("net.inet.ip.fw.verbose", NULL, 0,
		    &which, sizeof(which));
	} else if (_substrcmp(*av, "dyn_keepalive") == 0) {
		sysctlbyname("net.inet.ip.fw.dyn_keepalive", NULL, 0,
		    &which, sizeof(which));
#ifndef NO_ALTQ
	} else if (_substrcmp(*av, "altq") == 0) {
		altq_set_enabled(which);
#endif
	} else {
		warnx("unrecognize enable/disable keyword: %s\n", *av);
	}
}
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

/* Variables and functions */
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ *) ; 
 scalar_t__* ipf_devfiles ; 
 int /*<<< orphan*/ ** ipf_devs ; 
 int /*<<< orphan*/  ipf_event_dereg () ; 
 int /*<<< orphan*/  ipf_fbsd_sysctl_destroy () ; 
 int ipf_pfil_unhook () ; 
 int /*<<< orphan*/  ipf_unload_all () ; 
 char* ipfilter_version ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static int
ipf_modunload()
{
	int error, i;

	ipf_event_dereg();

	ipf_fbsd_sysctl_destroy();

	error = ipf_pfil_unhook();
	if (error != 0)
		return error;

	for (i = 0; ipf_devfiles[i]; i++) {
		if (ipf_devs[i] != NULL)
			destroy_dev(ipf_devs[i]);
	}

	ipf_unload_all();

	printf("%s unloaded\n", ipfilter_version);

	return (0);
}
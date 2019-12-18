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
 int EIO ; 
 int IPL_LOGSIZE ; 
 int /*<<< orphan*/  ipf_cdevsw ; 
 char** ipf_devfiles ; 
 int /*<<< orphan*/ ** ipf_devs ; 
 int /*<<< orphan*/  ipf_event_reg () ; 
 scalar_t__ ipf_fbsd_sysctl_create () ; 
 scalar_t__ ipf_load_all () ; 
 int ipf_pfil_hook () ; 
 int /*<<< orphan*/ * make_dev (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
ipf_modload()
{
	char *c, *str;
	int i, j, error;

	if (ipf_load_all() != 0)
		return EIO;

	if (ipf_fbsd_sysctl_create() != 0) {
		return EIO;
	}

	for (i = 0; i < IPL_LOGSIZE; i++)
		ipf_devs[i] = NULL;
	for (i = 0; (str = ipf_devfiles[i]); i++) {
		c = NULL;
		for(j = strlen(str); j > 0; j--)
			if (str[j] == '/') {
				c = str + j + 1;
				break;
			}
		if (!c)
			c = str;
		ipf_devs[i] = make_dev(&ipf_cdevsw, i, 0, 0, 0600, "%s", c);
	}

	error = ipf_pfil_hook();
	if (error != 0)
		return error;
	ipf_event_reg();

	return 0;
}
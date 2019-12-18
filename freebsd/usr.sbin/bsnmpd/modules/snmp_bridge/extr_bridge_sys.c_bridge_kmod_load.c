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
struct module_stat {int version; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int kldfirstmod (int) ; 
 scalar_t__ kldload (char const*) ; 
 int kldnext (int) ; 
 int modfnext (int) ; 
 scalar_t__ modstat (int,struct module_stat*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char const*) ; 

int
bridge_kmod_load(void)
{
	int fileid, modid;
	const char mod_name[] = "if_bridge";
	struct module_stat mstat;

	/* Scan files in kernel. */
	mstat.version = sizeof(struct module_stat);
	for (fileid = kldnext(0); fileid > 0; fileid = kldnext(fileid)) {
		/* Scan modules in file. */
		for (modid = kldfirstmod(fileid); modid > 0;
			modid = modfnext(modid)) {

			if (modstat(modid, &mstat) < 0)
				continue;

			if (strcmp(mod_name, mstat.name) == 0)
				return (0);
		}
	}

	/* Not present - load it. */
	if (kldload(mod_name) < 0) {
		syslog(LOG_ERR, "failed to load %s kernel module", mod_name);
		return (-1);
	}

	return (1);
}
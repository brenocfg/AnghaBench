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
 int /*<<< orphan*/  errno ; 
 int kldfirstmod (int) ; 
 scalar_t__ kldload (char const*) ; 
 int kldnext (int) ; 
 int modfnext (int) ; 
 scalar_t__ modstat (int,struct module_stat*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
wlan_kmod_load(const char *modname)
{
	int fileid, modid;
	struct module_stat mstat;

	mstat.version = sizeof(struct module_stat);
	for (fileid = kldnext(0); fileid > 0; fileid = kldnext(fileid)) {
		for (modid = kldfirstmod(fileid); modid > 0;
			modid = modfnext(modid)) {
			if (modstat(modid, &mstat) < 0)
				continue;
			if (strcmp(modname, mstat.name) == 0)
				return (0);
		}
	}

	/* Not present - load it. */
	if (kldload(modname) < 0) {
		syslog(LOG_ERR, "failed to load %s kernel module - %s", modname,
		    strerror(errno));
		return (-1);
	}

	return (1);
}
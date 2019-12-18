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
struct module_stat {int version; char* name; } ;
struct module_map_entry {char* ifname; char* kldname; } ;
typedef  int /*<<< orphan*/  ifname ;
typedef  int /*<<< orphan*/  ifkind ;

/* Variables and functions */
 int IFNAMSIZ ; 
 int MOD_PREFIX_LEN ; 
 scalar_t__ isdigit (char) ; 
 int kldfirstmod (int) ; 
 int /*<<< orphan*/  kldload (char*) ; 
 int kldnext (int) ; 
 int modfnext (int) ; 
 scalar_t__ modstat (int,struct module_stat*) ; 
 struct module_map_entry* module_map ; 
 int nitems (struct module_map_entry*) ; 
 scalar_t__ noload ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

void
ifmaybeload(const char *name)
{
#define MOD_PREFIX_LEN		3	/* "if_" */
	struct module_stat mstat;
	int i, fileid, modid;
	char ifkind[IFNAMSIZ + MOD_PREFIX_LEN], ifname[IFNAMSIZ], *dp;
	const char *cp;
	struct module_map_entry *mme;
	bool found;

	/* loading suppressed by the user */
	if (noload)
		return;

	/* trim the interface number off the end */
	strlcpy(ifname, name, sizeof(ifname));
	for (dp = ifname; *dp != 0; dp++)
		if (isdigit(*dp)) {
			*dp = 0;
			break;
		}

	/* Either derive it from the map or guess otherwise */
	*ifkind = '\0';
	found = false;
	for (i = 0; i < nitems(module_map); ++i) {
		mme = &module_map[i];
		if (strcmp(mme->ifname, ifname) == 0) {
			strlcpy(ifkind, mme->kldname, sizeof(ifkind));
			found = true;
			break;
		}
	}

	/* We didn't have an alias for it... we'll guess. */
	if (!found) {
	    /* turn interface and unit into module name */
	    strlcpy(ifkind, "if_", sizeof(ifkind));
	    strlcat(ifkind, ifname, sizeof(ifkind));
	}

	/* scan files in kernel */
	mstat.version = sizeof(struct module_stat);
	for (fileid = kldnext(0); fileid > 0; fileid = kldnext(fileid)) {
		/* scan modules in file */
		for (modid = kldfirstmod(fileid); modid > 0;
		     modid = modfnext(modid)) {
			if (modstat(modid, &mstat) < 0)
				continue;
			/* strip bus name if present */
			if ((cp = strchr(mstat.name, '/')) != NULL) {
				cp++;
			} else {
				cp = mstat.name;
			}
			/*
			 * Is it already loaded?  Don't compare with ifname if
			 * we were specifically told which kld to use.  Doing
			 * so could lead to conflicts not trivially solved.
			 */
			if ((!found && strcmp(ifname, cp) == 0) ||
			    strcmp(ifkind, cp) == 0)
				return;
		}
	}

	/*
	 * Try to load the module.  But ignore failures, because ifconfig can't
	 * infer the names of all drivers (eg mlx4en(4)).
	 */
	(void) kldload(ifkind);
}
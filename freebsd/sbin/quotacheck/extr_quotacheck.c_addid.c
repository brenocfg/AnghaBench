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
typedef  int u_long ;
struct fileusage {int fu_id; int /*<<< orphan*/  fu_name; struct fileusage* fu_next; } ;

/* Variables and functions */
 int FUHASH ; 
 int USRQUOTA ; 
 scalar_t__ aflag ; 
 int /*<<< orphan*/  bcopy (char*,int /*<<< orphan*/ ,int) ; 
 struct fileusage* calloc (int,int) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 struct fileusage*** fuhead ; 
 struct fileusage* lookup (int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 int strlen (char*) ; 
 scalar_t__ vflag ; 

struct fileusage *
addid(u_long id, int type, char *name, const char *fsname)
{
	struct fileusage *fup, **fhp;
	int len;

	if ((fup = lookup(id, type)) != NULL)
		return (fup);
	if (name)
		len = strlen(name);
	else
		len = 0;
	if ((fup = calloc(1, sizeof(*fup) + len)) == NULL)
		errx(1, "calloc failed");
	fhp = &fuhead[type][id & (FUHASH - 1)];
	fup->fu_next = *fhp;
	*fhp = fup;
	fup->fu_id = id;
	if (name)
		bcopy(name, fup->fu_name, len + 1);
	else {
		(void)sprintf(fup->fu_name, "%lu", id);
		if (vflag) {
			if (aflag && fsname != NULL)
				(void)printf("%s: ", fsname);
			printf("unknown %cid: %lu\n",
			    type == USRQUOTA ? 'u' : 'g', id);
		}
	}
	return (fup);
}
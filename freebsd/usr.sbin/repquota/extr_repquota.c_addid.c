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
 int /*<<< orphan*/  bcopy (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 struct fileusage*** fuhead ; 
 int* highid ; 
 struct fileusage* lookup (int,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 int strlen (char*) ; 

struct fileusage *
addid(u_long id, int type, char *name)
{
	struct fileusage *fup, **fhp;
	int len;

	if ((fup = lookup(id, type)))
		return (fup);
	if (name)
		len = strlen(name);
	else
		len = 10;
	if ((fup = (struct fileusage *)calloc(1, sizeof(*fup) + len)) == NULL)
		errx(1, "out of memory for fileusage structures");
	fhp = &fuhead[type][id & (FUHASH - 1)];
	fup->fu_next = *fhp;
	*fhp = fup;
	fup->fu_id = id;
	if (id > highid[type])
		highid[type] = id;
	if (name) {
		bcopy(name, fup->fu_name, len + 1);
	} else {
		sprintf(fup->fu_name, "%lu", id);
	}
	return (fup);
}
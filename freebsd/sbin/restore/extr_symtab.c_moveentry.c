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
struct entry {int /*<<< orphan*/  e_flags; int /*<<< orphan*/  e_name; int /*<<< orphan*/  e_namlen; struct entry* e_entries; struct entry* e_sibling; struct entry* e_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  TMPNAME ; 
 int /*<<< orphan*/  badentry (struct entry*,char*) ; 
 int /*<<< orphan*/  freename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gentempname (struct entry*) ; 
 struct entry* lookupparent (char*) ; 
 int /*<<< orphan*/  removeentry (struct entry*) ; 
 int /*<<< orphan*/  savename (char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* strrchr (char*,char) ; 

void
moveentry(struct entry *ep, char *newname)
{
	struct entry *np;
	char *cp;

	np = lookupparent(newname);
	if (np == NULL)
		badentry(ep, "cannot move ROOT");
	if (np != ep->e_parent) {
		removeentry(ep);
		ep->e_parent = np;
		ep->e_sibling = np->e_entries;
		np->e_entries = ep;
	}
	cp = strrchr(newname, '/') + 1;
	freename(ep->e_name);
	ep->e_name = savename(cp);
	ep->e_namlen = strlen(cp);
	if (strcmp(gentempname(ep), ep->e_name) == 0)
		ep->e_flags |= TMPNAME;
	else
		ep->e_flags &= ~TMPNAME;
}
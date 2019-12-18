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
struct entry {int e_flags; int /*<<< orphan*/  e_name; int /*<<< orphan*/  e_namlen; } ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int TMPNAME ; 
 int /*<<< orphan*/  badentry (struct entry*,char*) ; 
 int /*<<< orphan*/  freename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gentempname (struct entry*) ; 
 int /*<<< orphan*/  myname (struct entry*) ; 
 int /*<<< orphan*/  renameit (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  savename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

void
mktempname(struct entry *ep)
{
	char oldname[MAXPATHLEN];

	if (ep->e_flags & TMPNAME)
		badentry(ep, "mktempname: called with TMPNAME");
	ep->e_flags |= TMPNAME;
	(void) strcpy(oldname, myname(ep));
	freename(ep->e_name);
	ep->e_name = savename(gentempname(ep));
	ep->e_namlen = strlen(ep->e_name);
	renameit(oldname, myname(ep));
}
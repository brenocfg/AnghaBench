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
struct entry {scalar_t__ e_type; int /*<<< orphan*/  e_flags; } ;

/* Variables and functions */
 scalar_t__ LEAF ; 
 int /*<<< orphan*/  Nflag ; 
 int /*<<< orphan*/  REMOVED ; 
 int /*<<< orphan*/  TMPNAME ; 
 int /*<<< orphan*/  badentry (struct entry*,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 char* myname (struct entry*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ undelete (char*) ; 
 int /*<<< orphan*/  vprintf (int /*<<< orphan*/ ,char*,char*) ; 

void
delwhiteout(struct entry *ep)
{
	char *name;

	if (ep->e_type != LEAF)
		badentry(ep, "delwhiteout: not a leaf");
	ep->e_flags |= REMOVED;
	ep->e_flags &= ~TMPNAME;
	name = myname(ep);
	if (!Nflag && undelete(name) < 0) {
		fprintf(stderr, "warning: cannot delete whiteout %s: %s\n",
		    name, strerror(errno));
		return;
	}
	vprintf(stdout, "Delete whiteout %s\n", name);
}
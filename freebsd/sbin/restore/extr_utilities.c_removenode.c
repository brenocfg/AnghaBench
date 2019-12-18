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
struct entry {scalar_t__ e_type; int /*<<< orphan*/  e_flags; int /*<<< orphan*/ * e_entries; } ;

/* Variables and functions */
 scalar_t__ NODE ; 
 int /*<<< orphan*/  Nflag ; 
 int /*<<< orphan*/  REMOVED ; 
 int /*<<< orphan*/  TMPNAME ; 
 int /*<<< orphan*/  badentry (struct entry*,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 char* myname (struct entry*) ; 
 scalar_t__ rmdir (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vprintf (int /*<<< orphan*/ ,char*,char*) ; 

void
removenode(struct entry *ep)
{
	char *cp;

	if (ep->e_type != NODE)
		badentry(ep, "removenode: not a node");
	if (ep->e_entries != NULL)
		badentry(ep, "removenode: non-empty directory");
	ep->e_flags |= REMOVED;
	ep->e_flags &= ~TMPNAME;
	cp = myname(ep);
	if (!Nflag && rmdir(cp) < 0) {
		fprintf(stderr, "warning: %s: %s\n", cp, strerror(errno));
		return;
	}
	vprintf(stdout, "Remove node %s\n", cp);
}
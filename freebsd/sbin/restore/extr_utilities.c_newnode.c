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
 int /*<<< orphan*/  EXISTED ; 
 scalar_t__ NODE ; 
 int /*<<< orphan*/  Nflag ; 
 int /*<<< orphan*/  badentry (struct entry*,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 scalar_t__ mkdir (char*,int) ; 
 char* myname (struct entry*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uflag ; 
 int /*<<< orphan*/  vprintf (int /*<<< orphan*/ ,char*,char*) ; 

void
newnode(struct entry *np)
{
	char *cp;

	if (np->e_type != NODE)
		badentry(np, "newnode: not a node");
	cp = myname(np);
	if (!Nflag && mkdir(cp, 0777) < 0 && !uflag) {
		np->e_flags |= EXISTED;
		fprintf(stderr, "warning: %s: %s\n", cp, strerror(errno));
		return;
	}
	vprintf(stdout, "Make node %s\n", cp);
}
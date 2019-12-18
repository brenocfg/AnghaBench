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
struct entry {scalar_t__ e_type; scalar_t__ e_flags; struct entry* e_sibling; struct entry* e_entries; struct entry* e_next; } ;
typedef  scalar_t__ ino_t ;

/* Variables and functions */
 scalar_t__ LEAF ; 
 scalar_t__ TSTINO (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ UFS_ROOTINO ; 
 int /*<<< orphan*/  badentry (struct entry*,char*) ; 
 int /*<<< orphan*/  dprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dumpmap ; 
 int /*<<< orphan*/  freeentry (struct entry*) ; 
 struct entry* lookupino (scalar_t__) ; 
 scalar_t__ maxino ; 
 int /*<<< orphan*/  myname (struct entry*) ; 
 int /*<<< orphan*/  removeleaf (struct entry*) ; 
 struct entry* removelist ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  vprintf (int /*<<< orphan*/ ,char*) ; 

void
findunreflinks(void)
{
	struct entry *ep, *np;
	ino_t i;

	vprintf(stdout, "Find unreferenced names.\n");
	for (i = UFS_ROOTINO; i < maxino; i++) {
		ep = lookupino(i);
		if (ep == NULL || ep->e_type == LEAF || TSTINO(i, dumpmap) == 0)
			continue;
		for (np = ep->e_entries; np != NULL; np = np->e_sibling) {
			if (np->e_flags == 0) {
				dprintf(stdout,
				    "%s: remove unreferenced name\n",
				    myname(np));
				removeleaf(np);
				freeentry(np);
			}
		}
	}
	/*
	 * Any leaves remaining in removed directories is unreferenced.
	 */
	for (ep = removelist; ep != NULL; ep = ep->e_next) {
		for (np = ep->e_entries; np != NULL; np = np->e_sibling) {
			if (np->e_type == LEAF) {
				if (np->e_flags != 0)
					badentry(np, "unreferenced with flags");
				dprintf(stdout,
				    "%s: remove unreferenced name\n",
				    myname(np));
				removeleaf(np);
				freeentry(np);
			}
		}
	}
}
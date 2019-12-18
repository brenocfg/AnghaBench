#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct entry {scalar_t__ e_type; struct entry* e_next; int /*<<< orphan*/  e_ino; struct entry* e_links; TYPE_1__* e_parent; } ;
typedef  scalar_t__ ino_t ;
struct TYPE_2__ {scalar_t__ e_ino; } ;

/* Variables and functions */
 scalar_t__ LEAF ; 
 scalar_t__ TSTINO (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ UFS_ROOTINO ; 
 scalar_t__ UFS_WINO ; 
 int /*<<< orphan*/  deleteino (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delwhiteout (struct entry*) ; 
 int /*<<< orphan*/  dprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dumpmap ; 
 int /*<<< orphan*/  freeentry (struct entry*) ; 
 struct entry* lookupino (scalar_t__) ; 
 scalar_t__ maxino ; 
 int /*<<< orphan*/  mktempname (struct entry*) ; 
 int /*<<< orphan*/  myname (struct entry*) ; 
 int /*<<< orphan*/  removeleaf (struct entry*) ; 
 struct entry* removelist ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  usedinomap ; 
 int /*<<< orphan*/  vprintf (int /*<<< orphan*/ ,char*) ; 

void
removeoldleaves(void)
{
	struct entry *ep, *nextep;
	ino_t i, mydirino;

	vprintf(stdout, "Mark entries to be removed.\n");
	if ((ep = lookupino(UFS_WINO))) {
		vprintf(stdout, "Delete whiteouts\n");
		for ( ; ep != NULL; ep = nextep) {
			nextep = ep->e_links;
			mydirino = ep->e_parent->e_ino;
			/*
			 * We remove all whiteouts that are in directories
			 * that have been removed or that have been dumped.
			 */
			if (TSTINO(mydirino, usedinomap) &&
			    !TSTINO(mydirino, dumpmap))
				continue;
			delwhiteout(ep);
			freeentry(ep);
		}
	}
	for (i = UFS_ROOTINO + 1; i < maxino; i++) {
		ep = lookupino(i);
		if (ep == NULL)
			continue;
		if (TSTINO(i, usedinomap))
			continue;
		for ( ; ep != NULL; ep = ep->e_links) {
			dprintf(stdout, "%s: REMOVE\n", myname(ep));
			if (ep->e_type == LEAF) {
				removeleaf(ep);
				freeentry(ep);
			} else {
				mktempname(ep);
				deleteino(ep->e_ino);
				ep->e_next = removelist;
				removelist = ep;
			}
		}
	}
}
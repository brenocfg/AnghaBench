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
struct entry {int e_flags; scalar_t__ e_type; struct entry* e_links; } ;
typedef  scalar_t__ ino_t ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  HARDLINK ; 
 int NEW ; 
 scalar_t__ NODE ; 
 int /*<<< orphan*/  SYMLINK ; 
 scalar_t__ UFS_ROOTINO ; 
 scalar_t__ UFS_WINO ; 
 int /*<<< orphan*/  addwhiteout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linkit (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct entry* lookupino (scalar_t__) ; 
 scalar_t__ maxino ; 
 int /*<<< orphan*/  myname (struct entry*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vprintf (int /*<<< orphan*/ ,char*) ; 

void
createlinks(void)
{
	struct entry *np, *ep;
	ino_t i;
	char name[BUFSIZ];

	if ((ep = lookupino(UFS_WINO))) {
		vprintf(stdout, "Add whiteouts\n");
		for ( ; ep != NULL; ep = ep->e_links) {
			if ((ep->e_flags & NEW) == 0)
				continue;
			(void) addwhiteout(myname(ep));
			ep->e_flags &= ~NEW;
		}
	}
	vprintf(stdout, "Add links\n");
	for (i = UFS_ROOTINO; i < maxino; i++) {
		ep = lookupino(i);
		if (ep == NULL)
			continue;
		for (np = ep->e_links; np != NULL; np = np->e_links) {
			if ((np->e_flags & NEW) == 0)
				continue;
			(void) strcpy(name, myname(ep));
			if (ep->e_type == NODE) {
				(void) linkit(name, myname(np), SYMLINK);
			} else {
				(void) linkit(name, myname(np), HARDLINK);
			}
			np->e_flags &= ~NEW;
		}
	}
}
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
typedef  int /*<<< orphan*/  uintmax_t ;
struct entry {int /*<<< orphan*/  e_flags; } ;
typedef  scalar_t__ ino_t ;

/* Variables and functions */
 long FAIL ; 
 long GOOD ; 
 int LINK ; 
 int /*<<< orphan*/  NEW ; 
 int NODE ; 
 scalar_t__ TSTINO (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ UFS_WINO ; 
 struct entry* addentry (char*,scalar_t__,int) ; 
 char command ; 
 int /*<<< orphan*/  dprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  dumpmap ; 
 int /*<<< orphan*/  genliteraldir (char*,scalar_t__) ; 
 scalar_t__ hflag ; 
 struct entry* lookupino (scalar_t__) ; 
 int /*<<< orphan*/  mflag ; 
 int /*<<< orphan*/  myname (struct entry*) ; 
 int /*<<< orphan*/  newnode (struct entry*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vflag ; 

long
addfile(char *name, ino_t ino, int type)
{
	struct entry *ep;
	long descend = hflag ? GOOD : FAIL;
	char buf[100];

	if (TSTINO(ino, dumpmap) == 0) {
		dprintf(stdout, "%s: not on the tape\n", name);
		return (descend);
	}
	if (ino == UFS_WINO && command == 'i' && !vflag)
		return (descend);
	if (!mflag) {
		(void) sprintf(buf, "./%ju", (uintmax_t)ino);
		name = buf;
		if (type == NODE) {
			(void) genliteraldir(name, ino);
			return (descend);
		}
	}
	ep = lookupino(ino);
	if (ep != NULL) {
		if (strcmp(name, myname(ep)) == 0) {
			ep->e_flags |= NEW;
			return (descend);
		}
		type |= LINK;
	}
	ep = addentry(name, ino, type);
	if (type == NODE)
		newnode(ep);
	ep->e_flags |= NEW;
	return (descend);
}
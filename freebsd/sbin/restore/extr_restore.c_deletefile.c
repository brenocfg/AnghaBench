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
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 long FAIL ; 
 long GOOD ; 
 int /*<<< orphan*/  NEW ; 
 scalar_t__ NODE ; 
 int /*<<< orphan*/  REMOVED ; 
 scalar_t__ TSTINO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dumpmap ; 
 int /*<<< orphan*/  freeentry (struct entry*) ; 
 scalar_t__ hflag ; 
 struct entry* lookupname (char*) ; 

long
deletefile(char *name, ino_t ino, int type)
{
	long descend = hflag ? GOOD : FAIL;
	struct entry *ep;

	if (TSTINO(ino, dumpmap) == 0)
		return (descend);
	ep = lookupname(name);
	if (ep != NULL) {
		ep->e_flags &= ~NEW;
		ep->e_flags |= REMOVED;
		if (ep->e_type != NODE)
			freeentry(ep);
	}
	return (descend);
}
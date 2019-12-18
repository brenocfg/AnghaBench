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
struct entry {int e_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  d_ino; } ;

/* Variables and functions */
 int KEEP ; 
 int NEW ; 
 int /*<<< orphan*/  NODE ; 
 struct entry* addentry (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct entry* lookupname (char*) ; 
 int /*<<< orphan*/  newnode (struct entry*) ; 
 TYPE_1__* pathsearch (char*) ; 
 char* strchr (char*,char) ; 

void
pathcheck(char *name)
{
	char *cp;
	struct entry *ep;
	char *start;

	start = strchr(name, '/');
	if (start == NULL)
		return;
	for (cp = start; *cp != '\0'; cp++) {
		if (*cp != '/')
			continue;
		*cp = '\0';
		ep = lookupname(name);
		if (ep == NULL) {
			/* Safe; we know the pathname exists in the dump. */
			ep = addentry(name, pathsearch(name)->d_ino, NODE);
			newnode(ep);
		}
		ep->e_flags |= NEW|KEEP;
		*cp = '/';
	}
}
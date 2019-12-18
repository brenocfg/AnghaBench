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

/* Variables and functions */
 int /*<<< orphan*/  IN_LIST ; 
 int /*<<< orphan*/  NOT_IN_LIST ; 
 int /*<<< orphan*/  addentry (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  selhead ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  which ; 

__attribute__((used)) static void
maketypelist(char *fslist)
{
	char *ptr;

	if ((fslist == NULL) || (fslist[0] == '\0'))
		errx(1, "empty type list");

	if (fslist[0] == 'n' && fslist[1] == 'o') {
		fslist += 2;
		which = NOT_IN_LIST;
	}
	else
		which = IN_LIST;

	while ((ptr = strsep(&fslist, ",")) != NULL)
		addentry(&selhead, ptr, "");

}
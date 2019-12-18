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
struct group {int /*<<< orphan*/  gr_gid; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRPQUOTA ; 
 struct group* getgrnam (char*) ; 
 int showquotas (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

__attribute__((used)) static int
showgrpname(char *name)
{
	struct group *grp = getgrnam(name);

	if (grp == NULL) {
		warnx("%s: unknown group", name);
		return(1);
	}
	return(showquotas(GRPQUOTA, grp->gr_gid, name));
}
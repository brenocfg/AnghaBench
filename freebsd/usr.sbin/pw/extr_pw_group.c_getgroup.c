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
struct group {int dummy; } ;
typedef  scalar_t__ intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  EX_DATAERR ; 
 struct group* GETGRGID (scalar_t__) ; 
 struct group* GETGRNAM (char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static struct group *
getgroup(char *name, intmax_t id, bool fatal)
{
	struct group *grp;

	if (id < 0 && name == NULL)
		errx(EX_DATAERR, "groupname or id required");
	grp = (name != NULL) ? GETGRNAM(name) : GETGRGID(id);
	if (grp == NULL) {
		if (!fatal)
			return (NULL);
		if (name == NULL)
			errx(EX_DATAERR, "unknown gid `%ju'", id);
		errx(EX_DATAERR, "unknown group `%s'", name);
	}
	return (grp);
}
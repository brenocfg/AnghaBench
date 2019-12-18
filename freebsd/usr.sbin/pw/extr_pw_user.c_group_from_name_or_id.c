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
struct group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_NOUSER ; 
 struct group* GETGRGID (int /*<<< orphan*/ ) ; 
 struct group* GETGRNAM (char*) ; 
 int /*<<< orphan*/  GID_MAX ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  strtounum (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 

__attribute__((used)) static struct group *
group_from_name_or_id(char *name)
{
	const char *errstr = NULL;
	struct group *grp;
	uintmax_t id;

	if ((grp = GETGRNAM(name)) == NULL) {
		id = strtounum(name, 0, GID_MAX, &errstr);
		if (errstr)
			errx(EX_NOUSER, "group `%s' does not exist", name);
		grp = GETGRGID(id);
		if (grp == NULL)
			errx(EX_NOUSER, "group `%s' does not exist", name);
	}

	return (grp);
}
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
typedef  int /*<<< orphan*/  id_t ;

/* Variables and functions */
 struct group* getgrnam (char const*) ; 
 int /*<<< orphan*/  isnumber (char const) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strtod (char const*,char**) ; 
 int /*<<< orphan*/  warnx (char*,char const*,...) ; 

__attribute__((used)) static int
parse_group(const char *s, id_t *gidp, const char *unexpanded_rule)
{
	char *end;
	struct group *grp;

	grp = getgrnam(s);
	if (grp != NULL) {
		*gidp = grp->gr_gid;
		return (0);
	}

	if (!isnumber(s[0])) {
		warnx("malformed rule '%s': unknown group '%s'",
		    unexpanded_rule, s);
		return (1);
	}

	*gidp = strtod(s, &end);
	if ((size_t)(end - s) != strlen(s)) {
		warnx("malformed rule '%s': trailing characters "
		    "after numerical id", unexpanded_rule);
		return (1);
	}

	return (0);
}
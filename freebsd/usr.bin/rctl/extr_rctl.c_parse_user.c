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
struct passwd {int /*<<< orphan*/  pw_uid; } ;
typedef  int /*<<< orphan*/  id_t ;

/* Variables and functions */
 struct passwd* getpwnam (char const*) ; 
 int /*<<< orphan*/  isnumber (char const) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strtod (char const*,char**) ; 
 int /*<<< orphan*/  warnx (char*,char const*,...) ; 

__attribute__((used)) static int
parse_user(const char *s, id_t *uidp, const char *unexpanded_rule)
{
	char *end;
	struct passwd *pwd;

	pwd = getpwnam(s);
	if (pwd != NULL) {
		*uidp = pwd->pw_uid;
		return (0);
	}

	if (!isnumber(s[0])) {
		warnx("malformed rule '%s': unknown user '%s'",
		    unexpanded_rule, s);
		return (1);
	}

	*uidp = strtod(s, &end);
	if ((size_t)(end - s) != strlen(s)) {
		warnx("malformed rule '%s': trailing characters "
		    "after numerical id", unexpanded_rule);
		return (1);
	}

	return (0);
}
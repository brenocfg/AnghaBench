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
struct passwd {int /*<<< orphan*/  pw_gid; int /*<<< orphan*/  pw_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug (char*,...) ; 
 int /*<<< orphan*/  ga_free () ; 
 scalar_t__ ga_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ga_match_pattern_list (char const*) ; 
 struct passwd* getpwnam (char const*) ; 

__attribute__((used)) static int
match_cfg_line_group(const char *grps, int line, const char *user)
{
	int result = 0;
	struct passwd *pw;

	if (user == NULL)
		goto out;

	if ((pw = getpwnam(user)) == NULL) {
		debug("Can't match group at line %d because user %.100s does "
		    "not exist", line, user);
	} else if (ga_init(pw->pw_name, pw->pw_gid) == 0) {
		debug("Can't Match group because user %.100s not in any group "
		    "at line %d", user, line);
	} else if (ga_match_pattern_list(grps) != 1) {
		debug("user %.100s does not match group list %.100s at line %d",
		    user, grps, line);
	} else {
		debug("user %.100s matched group list %.100s at line %d", user,
		    grps, line);
		result = 1;
	}
out:
	ga_free();
	return result;
}
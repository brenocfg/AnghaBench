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
struct group {int /*<<< orphan*/  gr_gid; } ;
struct credentials {int /*<<< orphan*/  gid; TYPE_1__* pass; } ;
struct TYPE_2__ {int /*<<< orphan*/  pw_gid; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*,char const*) ; 
 struct group* getgrnam (char const*) ; 
 TYPE_1__* getpwnam (char const*) ; 

__attribute__((used)) static struct credentials *prepare_credentials(const char *user_name,
    const char *group_name)
{
	static struct credentials c;

	c.pass = getpwnam(user_name);
	if (!c.pass)
		die("user not found - %s", user_name);

	if (!group_name)
		c.gid = c.pass->pw_gid;
	else {
		struct group *group = getgrnam(group_name);
		if (!group)
			die("group not found - %s", group_name);

		c.gid = group->gr_gid;
	}

	return &c;
}
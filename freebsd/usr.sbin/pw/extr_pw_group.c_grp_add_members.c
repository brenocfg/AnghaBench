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
struct passwd {int /*<<< orphan*/  pw_name; } ;
struct group {int dummy; } ;

/* Variables and functions */
 struct group* gr_add (struct group*,int /*<<< orphan*/ ) ; 
 scalar_t__ grp_has_member (struct group*,int /*<<< orphan*/ ) ; 
 struct passwd* lookup_pwent (char*) ; 
 char* strtok (char*,char*) ; 

__attribute__((used)) static void
grp_add_members(struct group **grp, char *members)
{
	struct passwd *pwd;
	char *p;
	char tok[] = ", \t";

	if (members == NULL)
		return;
	for (p = strtok(members, tok); p != NULL; p = strtok(NULL, tok)) {
		pwd = lookup_pwent(p);
		if (grp_has_member(*grp, pwd->pw_name))
			continue;
		*grp = gr_add(*grp, pwd->pw_name);
	}
}
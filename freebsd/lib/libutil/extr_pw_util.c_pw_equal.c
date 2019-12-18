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
struct passwd {scalar_t__ pw_uid; scalar_t__ pw_gid; scalar_t__ pw_change; scalar_t__ pw_expire; int /*<<< orphan*/  pw_shell; int /*<<< orphan*/  pw_dir; int /*<<< orphan*/  pw_gecos; int /*<<< orphan*/  pw_class; int /*<<< orphan*/  pw_name; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
pw_equal(const struct passwd *pw1, const struct passwd *pw2)
{
	return (strcmp(pw1->pw_name, pw2->pw_name) == 0 &&
	    pw1->pw_uid == pw2->pw_uid &&
	    pw1->pw_gid == pw2->pw_gid &&
	    strcmp(pw1->pw_class, pw2->pw_class) == 0 &&
	    pw1->pw_change == pw2->pw_change &&
	    pw1->pw_expire == pw2->pw_expire &&
	    strcmp(pw1->pw_gecos, pw2->pw_gecos) == 0 &&
	    strcmp(pw1->pw_dir, pw2->pw_dir) == 0 &&
	    strcmp(pw1->pw_shell, pw2->pw_shell) == 0);
}
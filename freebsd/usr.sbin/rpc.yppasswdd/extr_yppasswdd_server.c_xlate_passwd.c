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
struct x_master_passwd {int /*<<< orphan*/  pw_fields; int /*<<< orphan*/  pw_expire; int /*<<< orphan*/  pw_shell; int /*<<< orphan*/  pw_dir; int /*<<< orphan*/  pw_gecos; int /*<<< orphan*/  pw_class; int /*<<< orphan*/  pw_change; int /*<<< orphan*/  pw_gid; int /*<<< orphan*/  pw_uid; int /*<<< orphan*/  pw_passwd; int /*<<< orphan*/  pw_name; } ;
struct passwd {int /*<<< orphan*/  pw_fields; int /*<<< orphan*/  pw_expire; int /*<<< orphan*/  pw_shell; int /*<<< orphan*/  pw_dir; int /*<<< orphan*/  pw_gecos; int /*<<< orphan*/  pw_class; int /*<<< orphan*/  pw_change; int /*<<< orphan*/  pw_gid; int /*<<< orphan*/  pw_uid; int /*<<< orphan*/  pw_passwd; int /*<<< orphan*/  pw_name; } ;

/* Variables and functions */

__attribute__((used)) static void
xlate_passwd(struct x_master_passwd *xpwd, struct passwd *pwd)
{
	pwd->pw_name = xpwd->pw_name;
	pwd->pw_passwd = xpwd->pw_passwd;
	pwd->pw_uid = xpwd->pw_uid;
	pwd->pw_gid = xpwd->pw_gid;
	pwd->pw_change = xpwd->pw_change;
	pwd->pw_class = xpwd->pw_class;
	pwd->pw_gecos = xpwd->pw_gecos;
	pwd->pw_dir = xpwd->pw_dir;
	pwd->pw_shell = xpwd->pw_shell;
	pwd->pw_expire = xpwd->pw_expire;
	pwd->pw_fields = xpwd->pw_fields;
}
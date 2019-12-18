#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct passwd {int /*<<< orphan*/  pw_expire; int /*<<< orphan*/  pw_shell; int /*<<< orphan*/  pw_dir; int /*<<< orphan*/  pw_gecos; int /*<<< orphan*/  pw_class; int /*<<< orphan*/  pw_change; int /*<<< orphan*/  pw_gid; int /*<<< orphan*/  pw_uid; int /*<<< orphan*/  pw_passwd; int /*<<< orphan*/  pw_name; } ;
struct TYPE_4__ {scalar_t__ pw_selected; int /*<<< orphan*/  pw_expire; void* pw_shell; void* pw_dir; void* pw_gecos; void* pw_class; int /*<<< orphan*/  pw_change; int /*<<< orphan*/  pw_gid; int /*<<< orphan*/  pw_uid; void* pw_passwd; void* pw_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  endpwent () ; 
 struct passwd* getpwent () ; 
 int npwds ; 
 TYPE_1__* pwds ; 
 int pwdsz ; 
 int /*<<< orphan*/  setpwent () ; 
 TYPE_1__* xrealloc (TYPE_1__*,int) ; 
 void* xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
get_users(void)
{
	struct passwd *pwd;

	setpwent();
	for (;;) {
		if (npwds == pwdsz) {
			pwdsz += pwdsz ? pwdsz : 128;
			pwds = xrealloc(pwds, pwdsz * sizeof *pwds);
		}
		if ((pwd = getpwent()) == NULL)
			break;
		pwds[npwds].pw_name = xstrdup(pwd->pw_name);
		pwds[npwds].pw_passwd = xstrdup(pwd->pw_passwd);
		pwds[npwds].pw_uid = pwd->pw_uid;
		pwds[npwds].pw_gid = pwd->pw_gid;
		pwds[npwds].pw_change = pwd->pw_change;
		pwds[npwds].pw_class = xstrdup(pwd->pw_class);
		pwds[npwds].pw_gecos = xstrdup(pwd->pw_gecos);
		pwds[npwds].pw_dir = xstrdup(pwd->pw_dir);
		pwds[npwds].pw_shell = xstrdup(pwd->pw_shell);
		pwds[npwds].pw_expire = pwd->pw_expire;
		pwds[npwds].pw_selected = 0;
		npwds++;
	}
	endpwent();
}
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
struct passwd {int dummy; } ;
typedef  int /*<<< orphan*/  cap_channel_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  UID_ROOT ; 
 struct passwd* cap_getpwent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cap_getpwent_r (int /*<<< orphan*/ *,struct passwd*,char*,int,struct passwd**) ; 
 struct passwd* cap_getpwnam (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cap_getpwnam_r (int /*<<< orphan*/ *,char*,struct passwd*,char*,int,struct passwd**) ; 
 struct passwd* cap_getpwuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cap_getpwuid_r (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct passwd*,char*,int,struct passwd**) ; 
 int /*<<< orphan*/  cap_setpwent (int /*<<< orphan*/ *) ; 
 unsigned int passwd_fields (struct passwd*) ; 

__attribute__((used)) static bool
runtest_fields(cap_channel_t *cappwd, unsigned int expected)
{
	char buf[1024];
	struct passwd *pwd;
	struct passwd st;

//printf("expected=0x%x\n", expected);
	cap_setpwent(cappwd);
	pwd = cap_getpwent(cappwd);
	if ((passwd_fields(pwd) & ~expected) != 0)
		return (false);

	cap_setpwent(cappwd);
	cap_getpwent_r(cappwd, &st, buf, sizeof(buf), &pwd);
	if ((passwd_fields(pwd) & ~expected) != 0)
		return (false);

	pwd = cap_getpwnam(cappwd, "root");
	if ((passwd_fields(pwd) & ~expected) != 0)
		return (false);

	cap_getpwnam_r(cappwd, "root", &st, buf, sizeof(buf), &pwd);
	if ((passwd_fields(pwd) & ~expected) != 0)
		return (false);

	pwd = cap_getpwuid(cappwd, UID_ROOT);
	if ((passwd_fields(pwd) & ~expected) != 0)
		return (false);

	cap_getpwuid_r(cappwd, UID_ROOT, &st, buf, sizeof(buf), &pwd);
	if ((passwd_fields(pwd) & ~expected) != 0)
		return (false);

	return (true);
}
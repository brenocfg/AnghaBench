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
typedef  int /*<<< orphan*/  bufs ;
typedef  int /*<<< orphan*/  bufc ;

/* Variables and functions */
 unsigned int GETPWENT0 ; 
 unsigned int GETPWENT1 ; 
 unsigned int GETPWENT2 ; 
 unsigned int GETPWENT_R0 ; 
 unsigned int GETPWENT_R1 ; 
 unsigned int GETPWENT_R2 ; 
 unsigned int GETPWNAM ; 
 unsigned int GETPWNAM_R ; 
 unsigned int GETPWUID ; 
 unsigned int GETPWUID_R ; 
 int /*<<< orphan*/  UID_OPERATOR ; 
 int /*<<< orphan*/  UID_ROOT ; 
 struct passwd* cap_getpwent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cap_getpwent_r (int /*<<< orphan*/ *,struct passwd*,char*,int,struct passwd**) ; 
 struct passwd* cap_getpwnam (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cap_getpwnam_r (int /*<<< orphan*/ *,char*,struct passwd*,char*,int,struct passwd**) ; 
 struct passwd* cap_getpwuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cap_getpwuid_r (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct passwd*,char*,int,struct passwd**) ; 
 int /*<<< orphan*/  cap_setpwent (int /*<<< orphan*/ *) ; 
 struct passwd* getpwent () ; 
 int /*<<< orphan*/  getpwent_r (struct passwd*,char*,int,struct passwd**) ; 
 struct passwd* getpwnam (char*) ; 
 int /*<<< orphan*/  getpwnam_r (char*,struct passwd*,char*,int,struct passwd**) ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getpwuid_r (int /*<<< orphan*/ ,struct passwd*,char*,int,struct passwd**) ; 
 scalar_t__ passwd_compare (struct passwd*,struct passwd*) ; 
 int /*<<< orphan*/  setpwent () ; 

__attribute__((used)) static unsigned int
runtest_cmds(cap_channel_t *cappwd)
{
	char bufs[1024], bufc[1024];
	unsigned int result;
	struct passwd *pwds, *pwdc;
	struct passwd sts, stc;

	result = 0;

	setpwent();
	cap_setpwent(cappwd);

	pwds = getpwent();
	pwdc = cap_getpwent(cappwd);
	if (passwd_compare(pwds, pwdc)) {
		result |= GETPWENT0;
		pwds = getpwent();
		pwdc = cap_getpwent(cappwd);
		if (passwd_compare(pwds, pwdc))
			result |= GETPWENT1;
	}

	getpwent_r(&sts, bufs, sizeof(bufs), &pwds);
	cap_getpwent_r(cappwd, &stc, bufc, sizeof(bufc), &pwdc);
	if (passwd_compare(pwds, pwdc)) {
		result |= GETPWENT_R0;
		getpwent_r(&sts, bufs, sizeof(bufs), &pwds);
		cap_getpwent_r(cappwd, &stc, bufc, sizeof(bufc), &pwdc);
		if (passwd_compare(pwds, pwdc))
			result |= GETPWENT_R1;
	}

	setpwent();
	cap_setpwent(cappwd);

	getpwent_r(&sts, bufs, sizeof(bufs), &pwds);
	cap_getpwent_r(cappwd, &stc, bufc, sizeof(bufc), &pwdc);
	if (passwd_compare(pwds, pwdc))
		result |= GETPWENT_R2;

	pwds = getpwent();
	pwdc = cap_getpwent(cappwd);
	if (passwd_compare(pwds, pwdc))
		result |= GETPWENT2;

	pwds = getpwnam("root");
	pwdc = cap_getpwnam(cappwd, "root");
	if (passwd_compare(pwds, pwdc)) {
		pwds = getpwnam("operator");
		pwdc = cap_getpwnam(cappwd, "operator");
		if (passwd_compare(pwds, pwdc))
			result |= GETPWNAM;
	}

	getpwnam_r("root", &sts, bufs, sizeof(bufs), &pwds);
	cap_getpwnam_r(cappwd, "root", &stc, bufc, sizeof(bufc), &pwdc);
	if (passwd_compare(pwds, pwdc)) {
		getpwnam_r("operator", &sts, bufs, sizeof(bufs), &pwds);
		cap_getpwnam_r(cappwd, "operator", &stc, bufc, sizeof(bufc),
		    &pwdc);
		if (passwd_compare(pwds, pwdc))
			result |= GETPWNAM_R;
	}

	pwds = getpwuid(UID_ROOT);
	pwdc = cap_getpwuid(cappwd, UID_ROOT);
	if (passwd_compare(pwds, pwdc)) {
		pwds = getpwuid(UID_OPERATOR);
		pwdc = cap_getpwuid(cappwd, UID_OPERATOR);
		if (passwd_compare(pwds, pwdc))
			result |= GETPWUID;
	}

	getpwuid_r(UID_ROOT, &sts, bufs, sizeof(bufs), &pwds);
	cap_getpwuid_r(cappwd, UID_ROOT, &stc, bufc, sizeof(bufc), &pwdc);
	if (passwd_compare(pwds, pwdc)) {
		getpwuid_r(UID_OPERATOR, &sts, bufs, sizeof(bufs), &pwds);
		cap_getpwuid_r(cappwd, UID_OPERATOR, &stc, bufc, sizeof(bufc),
		    &pwdc);
		if (passwd_compare(pwds, pwdc))
			result |= GETPWUID_R;
	}

	return (result);
}
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
struct group {int dummy; } ;
typedef  int /*<<< orphan*/  cap_channel_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  GID_WHEEL ; 
 struct group* cap_getgrent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cap_getgrent_r (int /*<<< orphan*/ *,struct group*,char*,int,struct group**) ; 
 struct group* cap_getgrgid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cap_getgrgid_r (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct group*,char*,int,struct group**) ; 
 struct group* cap_getgrnam (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cap_getgrnam_r (int /*<<< orphan*/ *,char*,struct group*,char*,int,struct group**) ; 
 int /*<<< orphan*/  cap_setgrent (int /*<<< orphan*/ *) ; 
 unsigned int group_fields (struct group*) ; 

__attribute__((used)) static bool
runtest_fields(cap_channel_t *capgrp, unsigned int expected)
{
	char buf[1024];
	struct group *grp;
	struct group st;

	(void)cap_setgrent(capgrp);
	grp = cap_getgrent(capgrp);
	if (group_fields(grp) != expected)
		return (false);

	(void)cap_setgrent(capgrp);
	cap_getgrent_r(capgrp, &st, buf, sizeof(buf), &grp);
	if (group_fields(grp) != expected)
		return (false);

	grp = cap_getgrnam(capgrp, "wheel");
	if (group_fields(grp) != expected)
		return (false);

	cap_getgrnam_r(capgrp, "wheel", &st, buf, sizeof(buf), &grp);
	if (group_fields(grp) != expected)
		return (false);

	grp = cap_getgrgid(capgrp, GID_WHEEL);
	if (group_fields(grp) != expected)
		return (false);

	cap_getgrgid_r(capgrp, GID_WHEEL, &st, buf, sizeof(buf), &grp);
	if (group_fields(grp) != expected)
		return (false);

	return (true);
}
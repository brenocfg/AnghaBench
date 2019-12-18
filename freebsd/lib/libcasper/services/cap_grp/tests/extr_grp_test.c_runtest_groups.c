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
struct group {scalar_t__ const gr_gid; int /*<<< orphan*/  gr_name; } ;
typedef  scalar_t__ gid_t ;
typedef  int /*<<< orphan*/  cap_channel_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 struct group* cap_getgrent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cap_getgrent_r (int /*<<< orphan*/ *,struct group*,char*,int,struct group**) ; 
 struct group* cap_getgrgid (int /*<<< orphan*/ *,scalar_t__ const) ; 
 int /*<<< orphan*/  cap_getgrgid_r (int /*<<< orphan*/ *,scalar_t__ const,struct group*,char*,int,struct group**) ; 
 struct group* cap_getgrnam (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  cap_getgrnam_r (int /*<<< orphan*/ *,char const*,struct group*,char*,int,struct group**) ; 
 int /*<<< orphan*/  cap_setgrent (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
runtest_groups(cap_channel_t *capgrp, const char **names, const gid_t *gids,
    size_t ngroups)
{
	char buf[1024];
	struct group *grp;
	struct group st;
	unsigned int i, got;

	(void)cap_setgrent(capgrp);
	got = 0;
	for (;;) {
		grp = cap_getgrent(capgrp);
		if (grp == NULL)
			break;
		got++;
		for (i = 0; i < ngroups; i++) {
			if (strcmp(names[i], grp->gr_name) == 0 &&
			    gids[i] == grp->gr_gid) {
				break;
			}
		}
		if (i == ngroups)
			return (false);
	}
	if (got != ngroups)
		return (false);

	(void)cap_setgrent(capgrp);
	got = 0;
	for (;;) {
		cap_getgrent_r(capgrp, &st, buf, sizeof(buf), &grp);
		if (grp == NULL)
			break;
		got++;
		for (i = 0; i < ngroups; i++) {
			if (strcmp(names[i], grp->gr_name) == 0 &&
			    gids[i] == grp->gr_gid) {
				break;
			}
		}
		if (i == ngroups)
			return (false);
	}
	if (got != ngroups)
		return (false);

	for (i = 0; i < ngroups; i++) {
		grp = cap_getgrnam(capgrp, names[i]);
		if (grp == NULL)
			return (false);
	}

	for (i = 0; i < ngroups; i++) {
		cap_getgrnam_r(capgrp, names[i], &st, buf, sizeof(buf), &grp);
		if (grp == NULL)
			return (false);
	}

	for (i = 0; i < ngroups; i++) {
		grp = cap_getgrgid(capgrp, gids[i]);
		if (grp == NULL)
			return (false);
	}

	for (i = 0; i < ngroups; i++) {
		cap_getgrgid_r(capgrp, gids[i], &st, buf, sizeof(buf), &grp);
		if (grp == NULL)
			return (false);
	}

	return (true);
}
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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  gids ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ setgid (int /*<<< orphan*/ ) ; 
 scalar_t__ setgroups (int,int /*<<< orphan*/ *) ; 
 scalar_t__ setuid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_creds(const char *test, uid_t uid, gid_t gid)
{
	gid_t gids[1] = { gid };

	if (setgid(gid) < 0)
		err(-1, "test %s: setegid(%d)", test, gid);
	if (setgroups(sizeof(gids)/sizeof(gid_t), gids) < 0)
		err(-1, "test %s: setgroups(%d)", test, gid);
	if (setuid(uid) < 0)
		err(-1, "test %s: seteuid(%d)", test, uid);
}
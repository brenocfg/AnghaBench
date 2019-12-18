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
struct test {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GID_OWNER ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 scalar_t__ chown (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  confirm_sugid (char*,int,int) ; 
 int /*<<< orphan*/  err (int,char*,char*,char*) ; 
 int /*<<< orphan*/  fpath ; 

void
priv_vfs_clearsugid_chgrp(int asroot, int injail, struct test *test)
{

	if (chown(fpath, -1, asroot ? GID_WHEEL : GID_OWNER) < 0)
		err(-1, "priv_vfs_clearsugid_chgrp(%s, %s): chrgrp",
		    asroot ? "root" : "!root", injail ? "jail" : "!jail");
	confirm_sugid("priv_vfs_clearsugid_chgrp", asroot, injail);
}
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
 int /*<<< orphan*/  EA_DATA ; 
 int /*<<< orphan*/  EA_NAME ; 
 int /*<<< orphan*/  EA_NAMESPACE ; 
 int /*<<< orphan*/  EA_SIZE ; 
 int /*<<< orphan*/  confirm_sugid (char*,int,int) ; 
 int /*<<< orphan*/  err (int,char*,char*,char*) ; 
 scalar_t__ extattr_set_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpath ; 

void
priv_vfs_clearsugid_extattr(int asroot, int injail, struct test *test)
{

	if (extattr_set_file(fpath, EA_NAMESPACE, EA_NAME, EA_DATA, EA_SIZE)
	    < 0)
		err(-1,
		    "priv_vfs_clearsugid_extattr(%s, %s): extattr_set_file",
		    asroot ? "root" : "!root", injail ? "jail" : "!jail");
	confirm_sugid("priv_vfs_clearsugid_extattr", asroot, injail);
}
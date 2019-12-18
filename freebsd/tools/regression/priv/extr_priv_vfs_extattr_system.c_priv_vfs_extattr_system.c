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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EA_DATA ; 
 int /*<<< orphan*/  EA_NAME ; 
 int /*<<< orphan*/  EA_NAMESPACE ; 
 scalar_t__ EA_SIZE ; 
 int /*<<< orphan*/  EPERM ; 
 int /*<<< orphan*/  err (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  expect (char*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ extattr_set_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  fpath ; 

void
priv_vfs_extattr_system(int asroot, int injail, struct test *test)
{
	ssize_t ret;
	int error;

	ret = extattr_set_file(fpath, EA_NAMESPACE, EA_NAME, EA_DATA,
	    EA_SIZE);
	if (ret < 0)
		error = -1;
	else if (ret == EA_SIZE)
		error = 0;
	else
		err(-1, "priv_vfs_extattr_system: set returned %zd", ret);
	if (asroot && injail)
		expect("priv_vfs_extattr_system(asroot, injail)", error, -1,
		    EPERM);
	if (asroot && !injail)
		expect("priv_vfs_extattr_system(asroot, !injail)", error, 0,
		    0);
	if (!asroot && injail)
		expect("priv_vfs_extattr_system(!asroot, injail)", error, -1,
		    EPERM);
	if (!asroot && !injail)
		expect("priv_vfs_extattr_system(!asroot, !injail)", error,
		    -1, EPERM);
}
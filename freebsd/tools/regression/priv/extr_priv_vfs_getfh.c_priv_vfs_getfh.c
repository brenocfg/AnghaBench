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
typedef  int /*<<< orphan*/  fhandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  EPERM ; 
 int /*<<< orphan*/  expect (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpath ; 
 int getfh (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
priv_vfs_getfh(int asroot, int injail, struct test *test)
{
	fhandle_t fh;
	int error;

	error = getfh(fpath, &fh);
	if (asroot && injail)
		expect("priv_vfs_getfh(asroot, injail)", error, -1, EPERM);
	if (asroot && !injail)
		expect("priv_vfs_getfh(asroot, !injail)", error, 0, 0);
	if (!asroot && injail)
		expect("priv_vfs_getfh(!asroot, injail)", error, -1, EPERM);
	if (!asroot && !injail)
		expect("priv_vfs_getfh(!asroot, !injail)", error, -1, EPERM);
}
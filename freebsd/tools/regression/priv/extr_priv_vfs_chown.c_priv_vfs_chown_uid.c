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
 int /*<<< orphan*/  EPERM ; 
 int /*<<< orphan*/  UID_OWNER ; 
 int chown (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  expect (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpath ; 

void
priv_vfs_chown_uid(int asroot, int injail, struct test *test)
{
	int error;

	error = chown(fpath, UID_OWNER, -1);
	if (asroot && injail)
		expect("priv_vfs_chown_uid(root, jail)", error, 0, 0);
	if (asroot && !injail)
		expect("priv_vfs_chown_uid(root, !jail)", error, 0, 0);
	if (!asroot && injail)
		expect("priv_vfs_chown_uid(!root, jail)", error, -1, EPERM);
	if (!asroot && !injail)
		expect("priv_vfs_chown_uid(!root, !jail)", error, -1, EPERM);
}
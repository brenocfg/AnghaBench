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
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  O_WRONLY ; 
 int /*<<< orphan*/  fpath_none ; 
 int /*<<< orphan*/  fpath_read ; 
 int /*<<< orphan*/  fpath_readwrite ; 
 int /*<<< orphan*/  fpath_write ; 
 int /*<<< orphan*/  try_io (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
priv_vfs_readwrite_fowner(int asroot, int injail, struct test *test)
{

	try_io("priv_vfs_readwrite_fowner(none, O_RDONLY)", fpath_none,
	    asroot, injail, O_RDONLY, asroot ? 0 : -1, EACCES);
	try_io("priv_vfs_readwrite_fowner(none, O_WRONLY)", fpath_none,
	    asroot, injail, O_WRONLY, asroot ? 0 : -1, EACCES);
	try_io("priv_vfs_readwrite_fowner(none, O_RDWR)", fpath_none,
	    asroot, injail, O_RDWR, asroot ? 0 : -1, EACCES);

	try_io("priv_vfs_readwrite_fowner(read, O_RDONLY)", fpath_read,
	    asroot, injail, O_RDONLY, 0, 0);
	try_io("priv_vfs_readwrite_fowner(read, O_WRONLY)", fpath_read,
	    asroot, injail, O_WRONLY, asroot ? 0 : -1, EACCES);
	try_io("priv_vfs_readwrite_fowner(read, O_RDWR)", fpath_read,
	    asroot, injail, O_RDWR, asroot ? 0 : -1, EACCES);

	try_io("priv_vfs_readwrite_fowner(write, O_RDONLY)", fpath_write,
	    asroot, injail, O_RDONLY, asroot ? 0 : -1, EACCES);
	try_io("priv_vfs_readwrite_fowner(write, O_WRONLY)", fpath_write,
	    asroot, injail, O_WRONLY, 0, 0);
	try_io("priv_vfs_readwrite_fowner(write, O_RDWR)", fpath_write,
	    asroot, injail, O_RDWR, asroot ? 0 : -1, EACCES);

	try_io("priv_vfs_readwrite_fowner(write, O_RDONLY)", fpath_readwrite,
	    asroot, injail, O_RDONLY, 0, 0);
	try_io("priv_vfs_readwrite_fowner(write, O_WRONLY)", fpath_readwrite,
	    asroot, injail, O_WRONLY, 0, 0);
	try_io("priv_vfs_readwrite_fowner(write, O_RDWR)", fpath_readwrite,
	    asroot, injail, O_RDWR, 0, 0);
}
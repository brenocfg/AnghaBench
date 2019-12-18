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
struct statfs {int /*<<< orphan*/  f_mntonname; int /*<<< orphan*/  f_mntfromname; int /*<<< orphan*/  f_fstypename; int /*<<< orphan*/  f_charspare; int /*<<< orphan*/  f_spare; int /*<<< orphan*/  f_fsid; int /*<<< orphan*/  f_owner; int /*<<< orphan*/  f_namemax; int /*<<< orphan*/  f_asyncreads; int /*<<< orphan*/  f_syncreads; int /*<<< orphan*/  f_asyncwrites; int /*<<< orphan*/  f_syncwrites; int /*<<< orphan*/  f_ffree; int /*<<< orphan*/  f_files; int /*<<< orphan*/  f_bavail; int /*<<< orphan*/  f_bfree; int /*<<< orphan*/  f_blocks; int /*<<< orphan*/  f_iosize; int /*<<< orphan*/  f_bsize; int /*<<< orphan*/  f_flags; int /*<<< orphan*/  f_type; int /*<<< orphan*/  f_version; } ;
struct freebsd11_statfs {int /*<<< orphan*/  f_mntonname; int /*<<< orphan*/  f_mntfromname; int /*<<< orphan*/  f_fstypename; int /*<<< orphan*/  f_fsid; int /*<<< orphan*/  f_owner; int /*<<< orphan*/  f_namemax; int /*<<< orphan*/  f_asyncreads; int /*<<< orphan*/  f_syncreads; int /*<<< orphan*/  f_asyncwrites; int /*<<< orphan*/  f_syncwrites; int /*<<< orphan*/  f_ffree; int /*<<< orphan*/  f_files; int /*<<< orphan*/  f_bavail; int /*<<< orphan*/  f_bfree; int /*<<< orphan*/  f_blocks; int /*<<< orphan*/  f_iosize; int /*<<< orphan*/  f_bsize; int /*<<< orphan*/  f_flags; int /*<<< orphan*/  f_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATFS_VERSION ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline void
__statfs11_to_statfs(const struct freebsd11_statfs *sf11, struct statfs *sf)
{

	sf->f_version = STATFS_VERSION;
	sf->f_type = sf11->f_type;
	sf->f_flags = sf11->f_flags;
	sf->f_bsize = sf11->f_bsize;
	sf->f_iosize = sf11->f_iosize;
	sf->f_blocks = sf11->f_blocks;
	sf->f_bfree = sf11->f_bfree;
	sf->f_bavail = sf11->f_bavail;
	sf->f_files = sf11->f_files;
	sf->f_ffree = sf11->f_ffree;
	sf->f_syncwrites = sf11->f_syncwrites;
	sf->f_asyncwrites = sf11->f_asyncwrites;
	sf->f_syncreads = sf11->f_syncreads;
	sf->f_asyncreads = sf11->f_asyncreads;
	sf->f_namemax = sf11->f_namemax;
	sf->f_owner = sf11->f_owner;
	sf->f_fsid = sf11->f_fsid;
	memset(sf->f_spare, 0, sizeof(sf->f_spare));
	memset(sf->f_charspare, 0, sizeof(sf->f_charspare));
	strlcpy(sf->f_fstypename, sf11->f_fstypename, sizeof(sf->f_fstypename));
	strlcpy(sf->f_mntfromname, sf11->f_mntfromname, sizeof(sf->f_mntfromname));
	strlcpy(sf->f_mntonname, sf11->f_mntonname, sizeof(sf->f_mntonname));
}
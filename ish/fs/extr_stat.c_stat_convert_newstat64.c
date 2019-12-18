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
struct statbuf {int /*<<< orphan*/  ctime_nsec; int /*<<< orphan*/  ctime; int /*<<< orphan*/  mtime_nsec; int /*<<< orphan*/  mtime; int /*<<< orphan*/  atime_nsec; int /*<<< orphan*/  atime; int /*<<< orphan*/  blocks; int /*<<< orphan*/  blksize; int /*<<< orphan*/  size; int /*<<< orphan*/  rdev; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  nlink; int /*<<< orphan*/  mode; int /*<<< orphan*/  inode; int /*<<< orphan*/  dev; } ;
struct newstat64 {int /*<<< orphan*/  ctime_nsec; int /*<<< orphan*/  ctime; int /*<<< orphan*/  mtime_nsec; int /*<<< orphan*/  mtime; int /*<<< orphan*/  atime_nsec; int /*<<< orphan*/  atime; int /*<<< orphan*/  blocks; int /*<<< orphan*/  blksize; int /*<<< orphan*/  size; int /*<<< orphan*/  rdev; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  nlink; int /*<<< orphan*/  mode; int /*<<< orphan*/  ino; int /*<<< orphan*/  fucked_ino; int /*<<< orphan*/  dev; } ;

/* Variables and functions */

struct newstat64 stat_convert_newstat64(struct statbuf stat) {
    struct newstat64 newstat;
    newstat.dev = stat.dev;
    newstat.fucked_ino = stat.inode;
    newstat.ino = stat.inode;
    newstat.mode = stat.mode;
    newstat.nlink = stat.nlink;
    newstat.uid = stat.uid;
    newstat.gid = stat.gid;
    newstat.rdev = stat.rdev;
    newstat.size = stat.size;
    newstat.blksize = stat.blksize;
    newstat.blocks = stat.blocks;
    newstat.atime = stat.atime;
    newstat.atime_nsec = stat.atime_nsec;
    newstat.mtime = stat.mtime;
    newstat.mtime_nsec = stat.mtime_nsec;
    newstat.ctime = stat.ctime;
    newstat.ctime_nsec = stat.ctime_nsec;
    return newstat;
}
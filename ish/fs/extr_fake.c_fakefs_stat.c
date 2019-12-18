#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct statbuf {int /*<<< orphan*/  rdev; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  mode; int /*<<< orphan*/  inode; } ;
struct mount {int dummy; } ;
struct ish_stat {int /*<<< orphan*/  rdev; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  mode; } ;
typedef  int /*<<< orphan*/  ino_t ;
struct TYPE_2__ {int (* stat ) (struct mount*,char const*,struct statbuf*,int) ;} ;

/* Variables and functions */
 int _ENOENT ; 
 int /*<<< orphan*/  db_begin (struct mount*) ; 
 int /*<<< orphan*/  db_commit (struct mount*) ; 
 int /*<<< orphan*/  db_rollback (struct mount*) ; 
 int /*<<< orphan*/  path_read_stat (struct mount*,char const*,struct ish_stat*,int /*<<< orphan*/ *) ; 
 TYPE_1__ realfs ; 
 int stub1 (struct mount*,char const*,struct statbuf*,int) ; 

__attribute__((used)) static int fakefs_stat(struct mount *mount, const char *path, struct statbuf *fake_stat, bool follow_links) {
    db_begin(mount);
    struct ish_stat ishstat;
    ino_t inode;
    if (!path_read_stat(mount, path, &ishstat, &inode)) {
        db_rollback(mount);
        return _ENOENT;
    }
    int err = realfs.stat(mount, path, fake_stat, follow_links);
    db_commit(mount);
    if (err < 0)
        return err;
    fake_stat->inode = inode;
    fake_stat->mode = ishstat.mode;
    fake_stat->uid = ishstat.uid;
    fake_stat->gid = ishstat.gid;
    fake_stat->rdev = ishstat.rdev;
    return 0;
}
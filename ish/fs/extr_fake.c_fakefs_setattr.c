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
struct mount {int dummy; } ;
struct ish_stat {int dummy; } ;
struct attr {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  ino_t ;
struct TYPE_2__ {int (* setattr ) (struct mount*,char const*,struct attr) ;} ;

/* Variables and functions */
 int _ENOENT ; 
 scalar_t__ attr_size ; 
 int /*<<< orphan*/  db_begin (struct mount*) ; 
 int /*<<< orphan*/  db_commit (struct mount*) ; 
 int /*<<< orphan*/  db_rollback (struct mount*) ; 
 int /*<<< orphan*/  fake_stat_setattr (struct ish_stat*,struct attr) ; 
 int /*<<< orphan*/  inode_write_stat (struct mount*,int /*<<< orphan*/ ,struct ish_stat*) ; 
 int /*<<< orphan*/  path_read_stat (struct mount*,char const*,struct ish_stat*,int /*<<< orphan*/ *) ; 
 TYPE_1__ realfs ; 
 int stub1 (struct mount*,char const*,struct attr) ; 

__attribute__((used)) static int fakefs_setattr(struct mount *mount, const char *path, struct attr attr) {
    if (attr.type == attr_size)
        return realfs.setattr(mount, path, attr);
    db_begin(mount);
    struct ish_stat ishstat;
    ino_t inode;
    if (!path_read_stat(mount, path, &ishstat, &inode)) {
        db_rollback(mount);
        return _ENOENT;
    }
    fake_stat_setattr(&ishstat, attr);
    inode_write_stat(mount, inode, &ishstat);
    db_commit(mount);
    return 0;
}
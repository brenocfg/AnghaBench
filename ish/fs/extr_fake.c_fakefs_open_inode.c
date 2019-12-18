#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * path_from_inode; } ;
struct mount {TYPE_1__ stmt; } ;
struct fd {int /*<<< orphan*/ * ops; int /*<<< orphan*/  fake_inode; } ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  ino_t ;
struct TYPE_4__ {struct fd* (* open ) (struct mount*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct fd* ERR_PTR (scalar_t__) ; 
 int /*<<< orphan*/  O_RDONLY_ ; 
 int /*<<< orphan*/  O_RDWR_ ; 
 scalar_t__ PTR_ERR (struct fd*) ; 
 scalar_t__ _EISDIR ; 
 scalar_t__ _ENOENT ; 
 int /*<<< orphan*/  db_begin (struct mount*) ; 
 int /*<<< orphan*/  db_commit (struct mount*) ; 
 int /*<<< orphan*/  db_exec (struct mount*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  db_reset (struct mount*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  db_rollback (struct mount*) ; 
 int /*<<< orphan*/  fakefs_fdops ; 
 TYPE_2__ realfs ; 
 int /*<<< orphan*/  sqlite3_bind_int64 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct fd* stub1 (struct mount*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fd* stub2 (struct mount*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct fd *fakefs_open_inode(struct mount *mount, ino_t inode) {
    db_begin(mount);
    sqlite3_stmt *stmt = mount->stmt.path_from_inode;
    sqlite3_bind_int64(stmt, 1, inode);
step:
    if (!db_exec(mount, stmt)) {
        db_reset(mount, stmt);
        db_rollback(mount);
        return ERR_PTR(_ENOENT);
    }
    const char *path = (const char *) sqlite3_column_text(stmt, 0);
    struct fd *fd = realfs.open(mount, path, O_RDWR_, 0);
    if (PTR_ERR(fd) == _EISDIR)
        fd = realfs.open(mount, path, O_RDONLY_, 0);
    if (PTR_ERR(fd) == _ENOENT)
        goto step;
    db_reset(mount, stmt);
    db_commit(mount);
    fd->fake_inode = inode;
    fd->ops = &fakefs_fdops;
    return fd;
}
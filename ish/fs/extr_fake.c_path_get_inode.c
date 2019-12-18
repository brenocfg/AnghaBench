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
struct TYPE_2__ {int /*<<< orphan*/  path_get_inode; } ;
struct mount {TYPE_1__ stmt; } ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  bind_path (int /*<<< orphan*/ ,int,char const*) ; 
 scalar_t__ db_exec (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  db_reset (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_column_int64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ino_t path_get_inode(struct mount *mount, const char *path) {
    // select inode from paths where path = ?
    bind_path(mount->stmt.path_get_inode, 1, path);
    ino_t inode = 0;
    if (db_exec(mount, mount->stmt.path_get_inode))
        inode = sqlite3_column_int64(mount->stmt.path_get_inode, 0);
    db_reset(mount, mount->stmt.path_get_inode);
    return inode;
}
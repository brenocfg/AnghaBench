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
struct TYPE_2__ {int /*<<< orphan*/  inode_read_stat; } ;
struct mount {TYPE_1__ stmt; } ;
struct ish_stat {int dummy; } ;
typedef  scalar_t__ ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  db_exec (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  db_reset (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (char*,unsigned long long) ; 
 int /*<<< orphan*/  sqlite3_bind_int64 (int /*<<< orphan*/ ,int,scalar_t__) ; 
 scalar_t__ sqlite3_column_blob (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void inode_read_stat(struct mount *mount, ino_t inode, struct ish_stat *stat) {
    // select stat from stats where inode = ?
    sqlite3_bind_int64(mount->stmt.inode_read_stat, 1, inode);
    if (!db_exec(mount, mount->stmt.inode_read_stat))
        die("inode_read_stat(%llu): missing inode", (unsigned long long) inode);
    *stat = *(struct ish_stat *) sqlite3_column_blob(mount->stmt.inode_read_stat, 0);
    db_reset(mount, mount->stmt.inode_read_stat);
}
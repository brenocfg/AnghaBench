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
struct TYPE_2__ {int /*<<< orphan*/  path_read_stat; } ;
struct mount {TYPE_1__ stmt; } ;
struct ish_stat {int dummy; } ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  bind_path (int /*<<< orphan*/ ,int,char const*) ; 
 int db_exec (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  db_reset (struct mount*,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_column_blob (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_column_int64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool path_read_stat(struct mount *mount, const char *path, struct ish_stat *stat, ino_t *inode) {
    // select inode, stat from stats natural join paths where path = ?
    bind_path(mount->stmt.path_read_stat, 1, path);
    bool exists = db_exec(mount, mount->stmt.path_read_stat);
    if (exists) {
        if (inode)
            *inode = sqlite3_column_int64(mount->stmt.path_read_stat, 0);
        if (stat)
            *stat = *(struct ish_stat *) sqlite3_column_blob(mount->stmt.path_read_stat, 1);
    }
    db_reset(mount, mount->stmt.path_read_stat);
    return exists;
}
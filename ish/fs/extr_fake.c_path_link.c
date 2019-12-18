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
struct TYPE_2__ {int /*<<< orphan*/  path_link; } ;
struct mount {TYPE_1__ stmt; } ;
typedef  scalar_t__ ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  bind_path (int /*<<< orphan*/ ,int,char const*) ; 
 int /*<<< orphan*/  db_exec_reset (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (char*,char const*,char const*) ; 
 scalar_t__ path_get_inode (struct mount*,char const*) ; 
 int /*<<< orphan*/  sqlite3_bind_int64 (int /*<<< orphan*/ ,int,scalar_t__) ; 

__attribute__((used)) static void path_link(struct mount *mount, const char *src, const char *dst) {
    ino_t inode = path_get_inode(mount, src);
    if (inode == 0)
        die("fakefs link(%s, %s): nonexistent src path", src, dst);
    // insert or replace into paths (path, inode) values (?, ?)
    bind_path(mount->stmt.path_link, 1, dst);
    sqlite3_bind_int64(mount->stmt.path_link, 2, inode);
    db_exec_reset(mount, mount->stmt.path_link);
}
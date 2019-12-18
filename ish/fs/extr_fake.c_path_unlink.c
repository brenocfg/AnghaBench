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
struct TYPE_2__ {int /*<<< orphan*/  path_unlink; } ;
struct mount {TYPE_1__ stmt; } ;
typedef  scalar_t__ ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  bind_path (int /*<<< orphan*/ ,int,char const*) ; 
 int /*<<< orphan*/  db_exec_reset (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 scalar_t__ inode_is_orphaned (struct mount*,scalar_t__) ; 
 scalar_t__ path_get_inode (struct mount*,char const*) ; 
 int /*<<< orphan*/  try_cleanup_inode (struct mount*,scalar_t__) ; 

__attribute__((used)) static void path_unlink(struct mount *mount, const char *path) {
    ino_t inode = path_get_inode(mount, path);
    if (inode == 0)
        die("path_unlink(%s): nonexistent path", path);
    // delete from paths where path = ?
    bind_path(mount->stmt.path_unlink, 1, path);
    db_exec_reset(mount, mount->stmt.path_unlink);
    if (inode_is_orphaned(mount, inode))
        try_cleanup_inode(mount, inode);
}
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
struct fd {int /*<<< orphan*/  mount; int /*<<< orphan*/ * ops; } ;
struct dir_entry {char* name; int /*<<< orphan*/  inode; } ;
struct TYPE_2__ {int (* readdir ) (struct fd*,struct dir_entry*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  db_begin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  db_commit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fakefs_fdops ; 
 int /*<<< orphan*/  path_get_inode (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__ realfs_fdops ; 
 int /*<<< orphan*/  realfs_getpath (struct fd*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strrchr (char*,char) ; 
 int stub1 (struct fd*,struct dir_entry*) ; 

__attribute__((used)) static int fakefs_readdir(struct fd *fd, struct dir_entry *entry) {
    assert(fd->ops == &fakefs_fdops);
    int res;
retry:
    res = realfs_fdops.readdir(fd, entry);
    if (res <= 0)
        return res;

    // this is annoying
    char entry_path[MAX_PATH + 1];
    realfs_getpath(fd, entry_path);
    if (strcmp(entry->name, "..") == 0) {
        if (strcmp(entry_path, "") != 0) {
            *strrchr(entry_path, '/') = '\0';
        }
    } else if (strcmp(entry->name, ".") != 0) {
        // god I don't know what to do if this would overflow
        strcat(entry_path, "/");
        strcat(entry_path, entry->name);
    }

    db_begin(fd->mount);
    entry->inode = path_get_inode(fd->mount, entry_path);
    db_commit(fd->mount);
    // it's quite possible that due to some mishap there's no metadata for this file
    // so just skip this entry, instead of crashing the program, so there's hope for recovery
    if (entry->inode == 0)
        goto retry;
    return res;
}
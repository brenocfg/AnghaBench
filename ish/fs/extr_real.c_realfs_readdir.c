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
struct fd {int /*<<< orphan*/  dir; } ;
struct dirent {int /*<<< orphan*/  d_name; int /*<<< orphan*/  d_ino; } ;
struct dir_entry {int /*<<< orphan*/  name; int /*<<< orphan*/  inode; } ;

/* Variables and functions */
 scalar_t__ errno ; 
 int errno_map () ; 
 struct dirent* readdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  realfs_opendir (struct fd*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int realfs_readdir(struct fd *fd, struct dir_entry *entry) {
    realfs_opendir(fd);
    errno = 0;
    struct dirent *dirent = readdir(fd->dir);
    if (dirent == NULL) {
        if (errno != 0)
            return errno_map();
        else
            return 0;
    }
    entry->inode = dirent->d_ino;
    strcpy(entry->name, dirent->d_name);
    return 1;
}
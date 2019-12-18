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
struct timespec {int dummy; } ;
struct mount {int /*<<< orphan*/  root_fd; } ;

/* Variables and functions */
 int errno_map () ; 
 int /*<<< orphan*/  fix_path (char const*) ; 
 int utimensat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timespec*,int /*<<< orphan*/ ) ; 

int realfs_utime(struct mount *mount, const char *path, struct timespec atime, struct timespec mtime) {
    struct timespec times[2] = {atime, mtime};
    int err = utimensat(mount->root_fd, fix_path(path), times, 0);
    if (err < 0)
        return errno_map();
    return 0;
}
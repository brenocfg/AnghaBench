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
struct mount {int /*<<< orphan*/  root_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_REMOVEDIR ; 
 int errno_map () ; 
 int /*<<< orphan*/  fix_path (char const*) ; 
 int unlinkat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int realfs_rmdir(struct mount *mount, const char *path) {
    int err = unlinkat(mount->root_fd, fix_path(path), AT_REMOVEDIR);
    if (err < 0)
        return errno_map();
    return 0;
}
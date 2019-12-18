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
 int errno_map () ; 
 int symlinkat (char const*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int realfs_symlink(struct mount *mount, const char *target, const char *link) {
    int err = symlinkat(target, mount->root_fd, link);
    if (err < 0)
        return errno_map();
    return err;
}
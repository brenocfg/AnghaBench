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
 int /*<<< orphan*/  fix_path (char const*) ; 
 int linkat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int realfs_link(struct mount *mount, const char *src, const char *dst) {
    int res = linkat(mount->root_fd, fix_path(src), mount->root_fd, fix_path(dst), 0);
    if (res < 0)
        return errno_map();
    return res;
}
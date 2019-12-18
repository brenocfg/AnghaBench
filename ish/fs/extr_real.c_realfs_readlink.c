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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ errno_map () ; 
 int /*<<< orphan*/  fix_path (char const*) ; 
 scalar_t__ readlinkat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static ssize_t realfs_readlink(struct mount *mount, const char *path, char *buf, size_t bufsize) {
    ssize_t size = readlinkat(mount->root_fd, fix_path(path), buf, bufsize);
    if (size < 0)
        return errno_map();
    return size;
}
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
struct statbuf {int dummy; } ;
struct stat {int dummy; } ;
struct mount {int /*<<< orphan*/  root_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_SYMLINK_NOFOLLOW ; 
 int /*<<< orphan*/  copy_stat (struct statbuf*,struct stat*) ; 
 int errno_map () ; 
 int /*<<< orphan*/  fix_path (char const*) ; 
 scalar_t__ fstatat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct stat*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int realfs_stat(struct mount *mount, const char *path, struct statbuf *fake_stat, bool follow_links) {
    struct stat real_stat;
    if (fstatat(mount->root_fd, fix_path(path), &real_stat, follow_links ? 0 : AT_SYMLINK_NOFOLLOW) < 0)
        return errno_map();
    copy_stat(fake_stat, &real_stat);
    return 0;
}
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
struct fd {int /*<<< orphan*/  real_fd; int /*<<< orphan*/ * dir; } ;

/* Variables and functions */
 int close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int errno_map () ; 

int realfs_close(struct fd *fd) {
    if (fd->dir != NULL)
        closedir(fd->dir);
    int err = close(fd->real_fd);
    if (err < 0)
        return errno_map();
    return 0;
}
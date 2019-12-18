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
struct fd {int /*<<< orphan*/ * dir; int /*<<< orphan*/  real_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int dup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fdopendir (int) ; 

__attribute__((used)) static void realfs_opendir(struct fd *fd) {
    if (fd->dir == NULL) {
        int dirfd = dup(fd->real_fd);
        fd->dir = fdopendir(dirfd);
        // this should never get called on a non-directory
        assert(fd->dir != NULL);
    }
}
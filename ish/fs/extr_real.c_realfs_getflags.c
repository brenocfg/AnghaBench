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
struct fd {int /*<<< orphan*/  real_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_GETFL ; 
 int errno_map () ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open_flags_fake_from_real (int) ; 

int realfs_getflags(struct fd *fd) {
    int flags = fcntl(fd->real_fd, F_GETFL);
    if (flags < 0)
        return errno_map();
    return open_flags_fake_from_real(flags);
}
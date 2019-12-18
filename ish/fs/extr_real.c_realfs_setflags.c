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
typedef  int /*<<< orphan*/  dword_t ;

/* Variables and functions */
 int /*<<< orphan*/  F_SETFL ; 
 int errno_map () ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_flags_real_from_fake (int /*<<< orphan*/ ) ; 

int realfs_setflags(struct fd *fd, dword_t flags) {
    int ret = fcntl(fd->real_fd, F_SETFL, open_flags_real_from_fake(flags));
    if (ret < 0)
        return errno_map();
    return 0;
}
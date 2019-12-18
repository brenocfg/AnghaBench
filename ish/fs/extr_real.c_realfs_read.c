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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ errno_map () ; 
 scalar_t__ read (int /*<<< orphan*/ ,void*,size_t) ; 

ssize_t realfs_read(struct fd *fd, void *buf, size_t bufsize) {
    ssize_t res = read(fd->real_fd, buf, bufsize);
    if (res < 0)
        return errno_map();
    return res;
}
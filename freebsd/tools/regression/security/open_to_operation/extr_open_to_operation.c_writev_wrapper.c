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
struct iovec {size_t iov_len; void* iov_base; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  writev (int,struct iovec*,int) ; 

__attribute__((used)) static ssize_t
writev_wrapper(int d, const void *buf, size_t nbytes)
{
	struct iovec iov;

	iov.iov_base = (void *)buf;
	iov.iov_len = nbytes;
	return (writev(d, &iov, 1));
}
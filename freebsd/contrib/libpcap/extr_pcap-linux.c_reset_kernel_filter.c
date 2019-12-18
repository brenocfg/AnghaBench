#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ pcap_t ;
typedef  int /*<<< orphan*/  dummy ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 scalar_t__ ENONET ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_DETACH_FILTER ; 
 scalar_t__ errno ; 
 int setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int
reset_kernel_filter(pcap_t *handle)
{
	int ret;
	/*
	 * setsockopt() barfs unless it get a dummy parameter.
	 * valgrind whines unless the value is initialized,
	 * as it has no idea that setsockopt() ignores its
	 * parameter.
	 */
	int dummy = 0;

	ret = setsockopt(handle->fd, SOL_SOCKET, SO_DETACH_FILTER,
				   &dummy, sizeof(dummy));
	/*
	 * Ignore ENOENT - it means "we don't have a filter", so there
	 * was no filter to remove, and there's still no filter.
	 *
	 * Also ignore ENONET, as a lot of kernel versions had a
	 * typo where ENONET, rather than ENOENT, was returned.
	 */
	if (ret == -1 && errno != ENOENT && errno != ENONET)
		return -1;
	return 0;
}
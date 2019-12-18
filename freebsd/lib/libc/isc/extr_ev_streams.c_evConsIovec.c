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

/* Variables and functions */
 int /*<<< orphan*/  memset (struct iovec*,int,int) ; 

struct iovec
evConsIovec(void *buf, size_t cnt) {
	struct iovec ret;

	memset(&ret, 0xf5, sizeof ret);
	ret.iov_base = buf;
	ret.iov_len = cnt;
	return (ret);
}
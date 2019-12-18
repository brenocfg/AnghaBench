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
struct timespec {scalar_t__ tv_nsec; scalar_t__ member_1; scalar_t__ tv_sec; scalar_t__ member_0; } ;

/* Variables and functions */

__attribute__((used)) static __inline struct timespec
timespec_sub(struct timespec a, struct timespec b)
{
	struct timespec ret = { a.tv_sec - b.tv_sec, a.tv_nsec - b.tv_nsec };
	if (ret.tv_nsec < 0) {
		ret.tv_sec--;
		ret.tv_nsec += 1000000000;
	}
	return ret;
}
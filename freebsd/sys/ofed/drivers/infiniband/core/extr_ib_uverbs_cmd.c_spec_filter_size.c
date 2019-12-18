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
typedef  scalar_t__ u16 ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ memchr_inv (char*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static ssize_t spec_filter_size(void *kern_spec_filter, u16 kern_filter_size,
				u16 ib_real_filter_sz)
{
	/*
	 * User space filter structures must be 64 bit aligned, otherwise this
	 * may pass, but we won't handle additional new attributes.
	 */

	if (kern_filter_size > ib_real_filter_sz) {
		if (memchr_inv((char *)kern_spec_filter +
			       ib_real_filter_sz, 0,
			       kern_filter_size - ib_real_filter_sz))
			return -EINVAL;
		return ib_real_filter_sz;
	}
	return kern_filter_size;
}
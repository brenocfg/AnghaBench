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

/* Variables and functions */
 int /*<<< orphan*/  __memcpy_aligned_up (unsigned long,unsigned long,size_t) ; 
 int /*<<< orphan*/  __memcpy_unaligned_up (unsigned long,unsigned long,size_t) ; 

void * memcpy(void * dest, const void *src, size_t n)
{
	if (!(((unsigned long) dest ^ (unsigned long) src) & 7)) {
		__memcpy_aligned_up ((unsigned long) dest, (unsigned long) src,
				     n);
		return dest;
	}
	__memcpy_unaligned_up ((unsigned long) dest, (unsigned long) src, n);
	return dest;
}
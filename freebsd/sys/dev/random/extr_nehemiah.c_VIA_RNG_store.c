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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */

__attribute__((used)) static __inline size_t
VIA_RNG_store(void *buf)
{
	uint32_t retval = 0;
	uint32_t rate = 0;

#ifdef __GNUCLIKE_ASM
	__asm __volatile(
		"movl	$0,%%edx\n\t"
		"xstore"
			: "=a" (retval), "+d" (rate), "+D" (buf)
			:
			: "memory"
	);
#endif
	if (rate == 0)
		return (retval&0x1f);
	return (0);
}
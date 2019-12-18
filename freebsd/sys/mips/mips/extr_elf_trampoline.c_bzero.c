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
typedef  int vm_offset_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */

__attribute__((used)) static __inline void
bzero(void *addr, size_t count)
{
	char *tmp = (char *)addr;

	while (count > 0) {
		if (count >= 4 && !((vm_offset_t)tmp & 3)) {
			*(uint32_t *)tmp = 0;
			tmp += 4;
			count -= 4;
		} else {
			*tmp = 0;
			tmp++;
			count--;
		}
	}
}
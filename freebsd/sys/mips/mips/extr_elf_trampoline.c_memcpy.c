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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */

__attribute__((used)) static __inline void *
memcpy(void *dst, const void *src, size_t len)
{
	const char *s = src;
    	char *d = dst;

	while (len) {
		if (0 && len >= 4 && !((vm_offset_t)d & 3) &&
		    !((vm_offset_t)s & 3)) {
			*(uint32_t *)d = *(uint32_t *)s;
			s += 4;
			d += 4;
			len -= 4;
		} else {
			*d++ = *s++;
			len--;
		}
	}
	return (dst);
}
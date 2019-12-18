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

__attribute__((used)) static inline
void	nvme_le128toh(void *p)
{
#if _BYTE_ORDER != _LITTLE_ENDIAN
	/* Swap 16 bytes in place */
	char *tmp = (char*)p;
	char b;
	int i;
	for (i = 0; i < 8; i++) {
		b = tmp[i];
		tmp[i] = tmp[15-i];
		tmp[15-i] = b;
	}
#else
	(void)p;
#endif
}
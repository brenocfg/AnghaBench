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
typedef  int ushort ;
typedef  unsigned long ulong ;

/* Variables and functions */

__attribute__((used)) static unsigned long scan_sync(unsigned long raw, unsigned long end)
{
	ushort *ptr = (ushort *)raw, *endp = (ushort *)end;

	while (ptr < endp && *ptr++ != 0x4489)
		;
	if (ptr < endp) {
		while (*ptr == 0x4489 && ptr < endp)
			ptr++;
		return (ulong)ptr;
	}
	return 0;
}
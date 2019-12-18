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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 

__attribute__((used)) static void
_g_raid3_xor(uint64_t *src, uint64_t *dst, size_t size)
{

	KASSERT((size % 128) == 0, ("Invalid size: %zu.", size));
	for (; size > 0; size -= 128) {
		*dst++ ^= (*src++);
		*dst++ ^= (*src++);
		*dst++ ^= (*src++);
		*dst++ ^= (*src++);
		*dst++ ^= (*src++);
		*dst++ ^= (*src++);
		*dst++ ^= (*src++);
		*dst++ ^= (*src++);
		*dst++ ^= (*src++);
		*dst++ ^= (*src++);
		*dst++ ^= (*src++);
		*dst++ ^= (*src++);
		*dst++ ^= (*src++);
		*dst++ ^= (*src++);
		*dst++ ^= (*src++);
		*dst++ ^= (*src++);
	}
}
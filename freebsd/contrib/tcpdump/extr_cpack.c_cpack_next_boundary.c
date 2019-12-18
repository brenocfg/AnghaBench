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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */

const uint8_t *
cpack_next_boundary(const uint8_t *buf, const uint8_t *p, size_t alignment)
{
	size_t misalignment = (size_t)(p - buf) % alignment;

	if (misalignment == 0)
		return p;

	return p + (alignment - misalignment);
}
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
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */

__attribute__((used)) static size_t
store_gcov_uint64(void *buffer, size_t off, uint64_t v)
{
	uint32_t *data;

	if (buffer) {
		data = (void*)((caddr_t)buffer + off);

		data[0] = (v & 0xffffffffUL);
		data[1] = (v >> 32);
	}

	return sizeof(*data) * 2;
}
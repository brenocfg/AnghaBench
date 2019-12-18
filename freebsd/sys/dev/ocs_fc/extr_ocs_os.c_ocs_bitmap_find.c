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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ocs_bitmap_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  bit_ffc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  bit_set (int /*<<< orphan*/ *,int) ; 

int32_t
ocs_bitmap_find(ocs_bitmap_t *bitmap, uint32_t n_bits)
{
	int32_t		position = -1;

	bit_ffc(bitmap, n_bits, &position);

	if (-1 != position) {
		bit_set(bitmap, position);
	}

	return position;
}
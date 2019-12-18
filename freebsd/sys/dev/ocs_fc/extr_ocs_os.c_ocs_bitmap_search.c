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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ocs_bitmap_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  bit_ffc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  bit_ffs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

int32_t
ocs_bitmap_search(ocs_bitmap_t *bitmap, uint8_t set, uint32_t n_bits)
{
	int32_t		position;

	if (!bitmap) {
		return -1;
	}

	if (set) {
		bit_ffs(bitmap, n_bits, &position);
	} else {
		bit_ffc(bitmap, n_bits, &position);
	}

	return position;
}
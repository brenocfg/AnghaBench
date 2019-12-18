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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ archive_le32dec (int const*) ; 

__attribute__((used)) static
int verify_data(const uint8_t* data_ptr, int magic, int size) {
	int i = 0;

	/* This is how the test data inside test files was generated;
	 * we are re-generating it here and we check if our re-generated
	 * test data is the same as in the test file. If this test is
	 * failing it's either because there's a bug in the test case,
	 * or the unpacked data is corrupted. */

	for(i = 0; i < size / 4; ++i) {
		const int k = i + 1;
		const signed int* lptr = (const signed int*) &data_ptr[i * 4];
		signed int val = k * k - 3 * k + (1 + magic);

		if(val < 0)
			val = 0;

		/* *lptr is a value inside unpacked test file, val is the
		 * value that should be in the unpacked test file. */

		if(archive_le32dec(lptr) != (uint32_t) val)
			return 0;
	}

	return 1;
}
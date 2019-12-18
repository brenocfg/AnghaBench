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
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  otrx_create_append_zeros (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static ssize_t otrx_create_align(FILE *trx, size_t curr_offset, size_t alignment) {
	if (curr_offset & (alignment - 1)) {
		size_t length = alignment - (curr_offset % alignment);
		return otrx_create_append_zeros(trx, length);
	}

	return 0;
}
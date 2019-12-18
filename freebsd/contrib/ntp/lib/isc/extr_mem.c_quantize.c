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
 size_t ALIGNMENT_SIZE ; 

__attribute__((used)) static inline size_t
quantize(size_t size) {
	/*!
	 * Round up the result in order to get a size big
	 * enough to satisfy the request and be aligned on ALIGNMENT_SIZE
	 * byte boundaries.
	 */

	if (size == 0U)
		return (ALIGNMENT_SIZE);
	return ((size + ALIGNMENT_SIZE - 1) & (~(ALIGNMENT_SIZE - 1)));
}
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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  htobe64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
lio_swap_8B_data(uint64_t *data, uint32_t blocks)
{

	while (blocks) {
		*data = htobe64(*data);
		blocks--;
		data++;
	}
}
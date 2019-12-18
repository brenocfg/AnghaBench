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
typedef  int /*<<< orphan*/  uint32_t ;
struct table_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
ta_need_modify_radix(void *ta_state, struct table_info *ti, uint32_t count,
    uint64_t *pflags)
{

	/*
	 * radix does not require additional memory allocations
	 * other than nodes itself. Adding new masks to the tree do
	 * but we don't have any API to call (and we don't known which
	 * sizes do we need).
	 */
	return (0);
}
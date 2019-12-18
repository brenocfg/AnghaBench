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

__attribute__((used)) static int pt_sync_within_bounds(const uint8_t *pos, const uint8_t *begin,
				 const uint8_t *end)
{
	/* We allow @pos == @end representing the very end of the trace.
	 *
	 * This will result in -pte_eos when we actually try to read from @pos.
	 */
	return (begin <= pos) && (pos <= end);
}
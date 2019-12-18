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
typedef  scalar_t__ uint64_t ;
struct pt_config {int /*<<< orphan*/ * end; int /*<<< orphan*/ * begin; } ;

/* Variables and functions */
 int /*<<< orphan*/ * align (int /*<<< orphan*/  const*,int) ; 
 scalar_t__* psb_pattern ; 
 int /*<<< orphan*/ * pt_find_psb (int /*<<< orphan*/  const*,struct pt_config const*) ; 
 int /*<<< orphan*/  pt_sync_within_bounds (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int pte_eos ; 
 int pte_internal ; 

int pt_sync_forward(const uint8_t **sync, const uint8_t *pos,
		    const struct pt_config *config)
{
	const uint8_t *begin, *end, *start;

	if (!sync || !pos || !config)
		return -pte_internal;

	start = pos;
	begin = config->begin;
	end = config->end;

	if (!pt_sync_within_bounds(pos, begin, end))
		return -pte_internal;

	/* We search for a full 64bit word. It's OK to skip the current one. */
	pos = align(pos, sizeof(*psb_pattern));

	/* Search for the psb payload pattern in the buffer. */
	for (;;) {
		const uint8_t *current = pos;
		uint64_t val;

		pos += sizeof(uint64_t);
		if (end < pos)
			return -pte_eos;

		val = * (const uint64_t *) current;

		if ((val != psb_pattern[0]) && (val != psb_pattern[1]))
			continue;

		/* We found a 64bit word's worth of psb payload pattern. */
		current = pt_find_psb(pos, config);
		if (!current)
			continue;

		/* If @start points inside a PSB, we may find that one.  Ignore
		 * it unless @start points to its beginning.
		 */
		if (current < start)
			continue;

		*sync = current;
		return 0;
	}
}
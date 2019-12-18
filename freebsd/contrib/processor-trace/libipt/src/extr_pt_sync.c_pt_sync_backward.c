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
 scalar_t__* psb_pattern ; 
 int /*<<< orphan*/ * pt_find_psb (int /*<<< orphan*/  const*,struct pt_config const*) ; 
 int /*<<< orphan*/  pt_sync_within_bounds (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int pte_eos ; 
 int pte_internal ; 
 int /*<<< orphan*/ * truncate (int /*<<< orphan*/  const*,int) ; 

int pt_sync_backward(const uint8_t **sync, const uint8_t *pos,
		    const struct pt_config *config)
{
	const uint8_t *begin, *end;

	if (!sync || !pos || !config)
		return -pte_internal;

	begin = config->begin;
	end = config->end;

	if (!pt_sync_within_bounds(pos, begin, end))
		return -pte_internal;

	/* We search for a full 64bit word. It's OK to skip the current one. */
	pos = truncate(pos, sizeof(*psb_pattern));

	/* Search for the psb payload pattern in the buffer. */
	for (;;) {
		const uint8_t *next = pos;
		uint64_t val;

		pos -= sizeof(uint64_t);
		if (pos < begin)
			return -pte_eos;

		val = * (const uint64_t *) pos;

		if ((val != psb_pattern[0]) && (val != psb_pattern[1]))
			continue;

		/* We found a 64bit word's worth of psb payload pattern. */
		next = pt_find_psb(next, config);
		if (!next)
			continue;

		*sync = next;
		return 0;
	}
}
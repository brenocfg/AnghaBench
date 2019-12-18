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
typedef  int u64 ;
struct pg_state {int /*<<< orphan*/  seq; } ;
struct flag_info {int mask; int val; int shift; char* set; char* clear; scalar_t__ is_val; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (int /*<<< orphan*/ ,char*,char const*,...) ; 

__attribute__((used)) static void dump_flag_info(struct pg_state *st, const struct flag_info
		*flag, u64 pte, int num)
{
	unsigned int i;

	for (i = 0; i < num; i++, flag++) {
		const char *s = NULL;
		u64 val;

		/* flag not defined so don't check it */
		if (flag->mask == 0)
			continue;
		/* Some 'flags' are actually values */
		if (flag->is_val) {
			val = pte & flag->val;
			if (flag->shift)
				val = val >> flag->shift;
			seq_printf(st->seq, "  %s:%llx", flag->set, val);
		} else {
			if ((pte & flag->mask) == flag->val)
				s = flag->set;
			else
				s = flag->clear;
			if (s)
				seq_printf(st->seq, "  %s", s);
		}
	}
}
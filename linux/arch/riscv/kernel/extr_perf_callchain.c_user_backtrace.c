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
struct stackframe {unsigned long ra; unsigned long fp; } ;
struct perf_callchain_entry_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  buftail ;

/* Variables and functions */
 scalar_t__ __copy_from_user_inatomic (struct stackframe*,unsigned long*,int) ; 
 int /*<<< orphan*/  access_ok (unsigned long*,int) ; 
 int /*<<< orphan*/  perf_callchain_store (struct perf_callchain_entry_ctx*,unsigned long) ; 

__attribute__((used)) static unsigned long user_backtrace(struct perf_callchain_entry_ctx *entry,
				    unsigned long fp, unsigned long reg_ra)
{
	struct stackframe buftail;
	unsigned long ra = 0;
	unsigned long *user_frame_tail =
			(unsigned long *)(fp - sizeof(struct stackframe));

	/* Check accessibility of one struct frame_tail beyond */
	if (!access_ok(user_frame_tail, sizeof(buftail)))
		return 0;
	if (__copy_from_user_inatomic(&buftail, user_frame_tail,
				      sizeof(buftail)))
		return 0;

	if (reg_ra != 0)
		ra = reg_ra;
	else
		ra = buftail.ra;

	fp = buftail.fp;
	if (ra != 0)
		perf_callchain_store(entry, ra);
	else
		return 0;

	return fp;
}
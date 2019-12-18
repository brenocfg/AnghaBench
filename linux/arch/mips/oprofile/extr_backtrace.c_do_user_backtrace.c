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
struct stackframe {unsigned long sp; int /*<<< orphan*/  ra; } ;

/* Variables and functions */
 unsigned long THREAD_SIZE ; 
 int /*<<< orphan*/  oprofile_add_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unwind_user_frame (struct stackframe*,unsigned int const) ; 

__attribute__((used)) static inline void do_user_backtrace(unsigned long low_addr,
				     struct stackframe *frame,
				     unsigned int depth)
{
	const unsigned int max_instr_check = 512;
	const unsigned long high_addr = low_addr + THREAD_SIZE;

	while (depth-- && !unwind_user_frame(frame, max_instr_check)) {
		oprofile_add_trace(frame->ra);
		if (frame->sp < low_addr || frame->sp > high_addr)
			break;
	}
}
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
typedef  void* uint64_t ;
struct unwind_state {void* pc; void* fp; void* sp; } ;

/* Variables and functions */
 int /*<<< orphan*/  INKERNEL (void*) ; 

int
unwind_frame(struct unwind_state *frame)
{
	uint64_t fp;

	fp = frame->fp;
	if (!INKERNEL(fp))
		return (-1);

	frame->sp = fp + 0x10;
	/* FP to previous frame (X29) */
	frame->fp = *(uint64_t *)(fp);
	/* LR (X30) */
	frame->pc = *(uint64_t *)(fp + 8) - 4;

	return (0);
}
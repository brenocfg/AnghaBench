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
struct trapframe {int /*<<< orphan*/  srr0; int /*<<< orphan*/  lr; int /*<<< orphan*/ * fixreg; int /*<<< orphan*/  ctr; } ;

/* Variables and functions */
#define  DTRACE_INVOP_BCTR 131 
#define  DTRACE_INVOP_BLR 130 
#define  DTRACE_INVOP_JUMP 129 
#define  DTRACE_INVOP_MFLR_R0 128 
 int dtrace_invop (int /*<<< orphan*/ ,struct trapframe*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dtrace_invop_start(struct trapframe *frame)
{

	switch (dtrace_invop(frame->srr0, frame, frame->fixreg[3])) {
	case DTRACE_INVOP_JUMP:
		break;
	case DTRACE_INVOP_BCTR:
		frame->srr0 = frame->ctr;
		break;
	case DTRACE_INVOP_BLR:
		frame->srr0 = frame->lr;
		break;
	case DTRACE_INVOP_MFLR_R0:
		frame->fixreg[0] = frame->lr;
		frame->srr0 = frame->srr0 + 4;
		break;
	default:
		return (-1);
	}
	return (0);
}
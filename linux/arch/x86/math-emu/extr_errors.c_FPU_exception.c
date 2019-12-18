#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int type; int name; } ;

/* Variables and functions */
 int CW_Exceptions ; 
 int EX_INTERNAL ; 
 int EX_Precision ; 
 int /*<<< orphan*/  FPU_info ; 
 int /*<<< orphan*/  FPU_printall () ; 
 int /*<<< orphan*/  RE_ENTRANT_CHECK_OFF ; 
 int /*<<< orphan*/  RE_ENTRANT_CHECK_ON ; 
 int /*<<< orphan*/  SIGFPE ; 
 int SW_Backward ; 
 int SW_C1 ; 
 int SW_Exc_Mask ; 
 int SW_Stack_Fault ; 
 int SW_Summary ; 
 int control_word ; 
 TYPE_1__* exception_names ; 
 int /*<<< orphan*/  math_abort (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int partial_status ; 
 int /*<<< orphan*/  printk (char*,int) ; 

void FPU_exception(int n)
{
	int i, int_type;

	int_type = 0;		/* Needed only to stop compiler warnings */
	if (n & EX_INTERNAL) {
		int_type = n - EX_INTERNAL;
		n = EX_INTERNAL;
		/* Set lots of exception bits! */
		partial_status |= (SW_Exc_Mask | SW_Summary | SW_Backward);
	} else {
		/* Extract only the bits which we use to set the status word */
		n &= (SW_Exc_Mask);
		/* Set the corresponding exception bit */
		partial_status |= n;
		/* Set summary bits iff exception isn't masked */
		if (partial_status & ~control_word & CW_Exceptions)
			partial_status |= (SW_Summary | SW_Backward);
		if (n & (SW_Stack_Fault | EX_Precision)) {
			if (!(n & SW_C1))
				/* This bit distinguishes over- from underflow for a stack fault,
				   and roundup from round-down for precision loss. */
				partial_status &= ~SW_C1;
		}
	}

	RE_ENTRANT_CHECK_OFF;
	if ((~control_word & n & CW_Exceptions) || (n == EX_INTERNAL)) {
		/* Get a name string for error reporting */
		for (i = 0; exception_names[i].type; i++)
			if ((exception_names[i].type & n) ==
			    exception_names[i].type)
				break;

		if (exception_names[i].type) {
#ifdef PRINT_MESSAGES
			printk("FP Exception: %s!\n", exception_names[i].name);
#endif /* PRINT_MESSAGES */
		} else
			printk("FPU emulator: Unknown Exception: 0x%04x!\n", n);

		if (n == EX_INTERNAL) {
			printk("FPU emulator: Internal error type 0x%04x\n",
			       int_type);
			FPU_printall();
		}
#ifdef PRINT_MESSAGES
		else
			FPU_printall();
#endif /* PRINT_MESSAGES */

		/*
		 * The 80486 generates an interrupt on the next non-control FPU
		 * instruction. So we need some means of flagging it.
		 * We use the ES (Error Summary) bit for this.
		 */
	}
	RE_ENTRANT_CHECK_ON;

#ifdef __DEBUG__
	math_abort(FPU_info, SIGFPE);
#endif /* __DEBUG__ */

}
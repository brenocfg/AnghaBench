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
struct utrapframe {int uf_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  UF_DONE (struct utrapframe*) ; 
#define  UT_FP_EXCEPTION_IEEE_754 131 
#define  UT_FP_EXCEPTION_OTHER 130 
#define  UT_ILLEGAL_INSTRUCTION 129 
#define  UT_MEM_ADDRESS_NOT_ALIGNED 128 
 int __emul_insn (struct utrapframe*) ; 
 int __fpu_exception (struct utrapframe*) ; 
 int __unaligned_fixup (struct utrapframe*) ; 
 int /*<<< orphan*/  __utrap_kill_self (int) ; 
 int /*<<< orphan*/  __utrap_write (char*) ; 
 char** utrap_msg ; 

void
__sparc_utrap(struct utrapframe *uf)
{
	int sig;

	switch (uf->uf_type) {
	case UT_FP_EXCEPTION_IEEE_754:
	case UT_FP_EXCEPTION_OTHER:
		sig = __fpu_exception(uf);
		break;
	case UT_ILLEGAL_INSTRUCTION:
		sig = __emul_insn(uf);
		break;
	case UT_MEM_ADDRESS_NOT_ALIGNED:
		sig = __unaligned_fixup(uf);
		break;
	default:
		break;
	}
	if (sig) {
		__utrap_write("__sparc_utrap: fatal ");
		__utrap_write(utrap_msg[uf->uf_type]);
		__utrap_write("\n");
		__utrap_kill_self(sig);
	}
	UF_DONE(uf);
}
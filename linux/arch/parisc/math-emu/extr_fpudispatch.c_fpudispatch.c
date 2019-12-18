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
typedef  int u_int ;

/* Variables and functions */
 scalar_t__ FPUDEBUG ; 
 size_t FPU_TYPE_FLAG_POS ; 
#define  MAJOR_06_EXCP 133 
#define  MAJOR_0C_EXCP 132 
#define  MAJOR_0E_EXCP 131 
#define  MAJOR_26_EXCP 130 
#define  MAJOR_2E_EXCP 129 
 int PA2_0_FPU_FLAG ; 
#define  PA83_UNIMP_EXCP 128 
 int UNIMPLEMENTEDEXCEPTION ; 
 int /*<<< orphan*/  VASSERT (int) ; 
 int decode_06 (int,int*) ; 
 int decode_0c (int,int,int,int*) ; 
 int decode_0e (int,int,int,int*) ; 
 int decode_26 (int,int*) ; 
 int decode_2e (int,int*) ; 
 int get_class (int) ; 
 int get_subop (int) ; 
 int get_subop1_PA1_1 (int) ; 
 int get_subop1_PA2_0 (int) ; 
 int /*<<< orphan*/  parisc_linux_get_fpu_type (int*) ; 
 int /*<<< orphan*/  printk (char*,int,int) ; 

u_int
fpudispatch(u_int ir, u_int excp_code, u_int holder, u_int fpregs[])
{
	u_int class, subop;
	u_int fpu_type_flags;

	/* All FP emulation code assumes that ints are 4-bytes in length */
	VASSERT(sizeof(int) == 4);

	parisc_linux_get_fpu_type(fpregs);

	fpu_type_flags=fpregs[FPU_TYPE_FLAG_POS];  /* get fpu type flags */

	class = get_class(ir);
	if (class == 1) {
		if  (fpu_type_flags & PA2_0_FPU_FLAG)
			subop = get_subop1_PA2_0(ir);
		else
			subop = get_subop1_PA1_1(ir);
	}
	else
		subop = get_subop(ir);

	if (FPUDEBUG) printk("class %d subop %d\n", class, subop);

	switch (excp_code) {
		case MAJOR_0C_EXCP:
		case PA83_UNIMP_EXCP:
			return(decode_0c(ir,class,subop,fpregs));
		case MAJOR_0E_EXCP:
			return(decode_0e(ir,class,subop,fpregs));
		case MAJOR_06_EXCP:
			return(decode_06(ir,fpregs));
		case MAJOR_26_EXCP:
			return(decode_26(ir,fpregs));
		case MAJOR_2E_EXCP:
			return(decode_2e(ir,fpregs));
		default:
			/* "crashme Night Gallery painting nr 2. (asm_crash.s).
			 * This was fixed for multi-user kernels, but
			 * workstation kernels had a panic here.  This allowed
			 * any arbitrary user to panic the kernel by executing
			 * setting the FP exception registers to strange values
			 * and generating an emulation trap.  The emulation and
			 * exception code must never be able to panic the
			 * kernel.
			 */
			return(UNIMPLEMENTEDEXCEPTION);
	}
}
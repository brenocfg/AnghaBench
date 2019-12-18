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
typedef  int /*<<< orphan*/  u8 ;
struct pt_regs {int msr; unsigned long* gpr; unsigned long dar; int ccr; int xer; } ;
struct instruction_op {int type; unsigned int ea; size_t reg; unsigned long val; int vsx_flags; int update_reg; } ;

/* Variables and functions */
 int BYTEREV ; 
 int EACCES ; 
 int EFAULT ; 
 int EINVAL ; 
 int GETSIZE (int) ; 
 int GETTYPE (int) ; 
#define  LARX 139 
#define  LOAD 138 
#define  LOAD_FP 137 
#define  LOAD_MULTI 136 
#define  LOAD_VMX 135 
#define  LOAD_VSX 134 
 int MSR_FP ; 
 int MSR_KERNEL ; 
 int MSR_LE ; 
 int MSR_PR ; 
 unsigned long MSR_VEC ; 
 unsigned long MSR_VSX ; 
 int SIGNEXT ; 
 int /*<<< orphan*/  STACK_INT_FRAME_SIZE ; 
#define  STCX 133 
#define  STORE 132 
#define  STORE_FP 131 
#define  STORE_MULTI 130 
#define  STORE_VMX 129 
#define  STORE_VSX 128 
 int UPDATE ; 
 int VSX_CHECK_VEC ; 
 int /*<<< orphan*/  __get_user_asmx (unsigned long,unsigned long,int,char*) ; 
 int /*<<< orphan*/  __put_user_asmx (unsigned long,unsigned long,int,char*,unsigned int) ; 
 int /*<<< orphan*/  address_ok (struct pt_regs*,unsigned long,int) ; 
 unsigned int byterev_4 (unsigned int) ; 
 int copy_mem_in (int /*<<< orphan*/ *,unsigned long,int,struct pt_regs*) ; 
 int copy_mem_out (int /*<<< orphan*/ *,unsigned long,int,struct pt_regs*) ; 
 int /*<<< orphan*/  do_byterev (unsigned long*,int) ; 
 int do_fp_load (struct instruction_op*,unsigned long,struct pt_regs*,int) ; 
 int do_fp_store (struct instruction_op*,unsigned long,struct pt_regs*,int) ; 
 int do_lqarx (unsigned long,unsigned long*) ; 
 int /*<<< orphan*/  do_signext (unsigned long*,int) ; 
 int do_stqcx (unsigned long,unsigned long,unsigned long,unsigned int*) ; 
 int do_vec_load (size_t,unsigned long,int,struct pt_regs*,int) ; 
 int do_vec_store (int,unsigned long,int,struct pt_regs*,int) ; 
 int do_vsx_load (struct instruction_op*,unsigned long,struct pt_regs*,int) ; 
 int do_vsx_store (struct instruction_op*,unsigned long,struct pt_regs*,int) ; 
 int emulate_lq (struct pt_regs*,unsigned long,size_t,int) ; 
 int emulate_stq (struct pt_regs*,unsigned long,int,int) ; 
 int handle_stack_update (unsigned long,struct pt_regs*) ; 
 int read_mem (unsigned long*,unsigned long,int,struct pt_regs*) ; 
 unsigned long truncate_if_32bit (int,unsigned int) ; 
 int /*<<< orphan*/  unlikely (int) ; 
 int write_mem (unsigned long,unsigned long,int,struct pt_regs*) ; 

int emulate_loadstore(struct pt_regs *regs, struct instruction_op *op)
{
	int err, size, type;
	int i, rd, nb;
	unsigned int cr;
	unsigned long val;
	unsigned long ea;
	bool cross_endian;

	err = 0;
	size = GETSIZE(op->type);
	type = GETTYPE(op->type);
	cross_endian = (regs->msr & MSR_LE) != (MSR_KERNEL & MSR_LE);
	ea = truncate_if_32bit(regs->msr, op->ea);

	switch (type) {
	case LARX:
		if (ea & (size - 1))
			return -EACCES;		/* can't handle misaligned */
		if (!address_ok(regs, ea, size))
			return -EFAULT;
		err = 0;
		val = 0;
		switch (size) {
#ifdef __powerpc64__
		case 1:
			__get_user_asmx(val, ea, err, "lbarx");
			break;
		case 2:
			__get_user_asmx(val, ea, err, "lharx");
			break;
#endif
		case 4:
			__get_user_asmx(val, ea, err, "lwarx");
			break;
#ifdef __powerpc64__
		case 8:
			__get_user_asmx(val, ea, err, "ldarx");
			break;
		case 16:
			err = do_lqarx(ea, &regs->gpr[op->reg]);
			break;
#endif
		default:
			return -EINVAL;
		}
		if (err) {
			regs->dar = ea;
			break;
		}
		if (size < 16)
			regs->gpr[op->reg] = val;
		break;

	case STCX:
		if (ea & (size - 1))
			return -EACCES;		/* can't handle misaligned */
		if (!address_ok(regs, ea, size))
			return -EFAULT;
		err = 0;
		switch (size) {
#ifdef __powerpc64__
		case 1:
			__put_user_asmx(op->val, ea, err, "stbcx.", cr);
			break;
		case 2:
			__put_user_asmx(op->val, ea, err, "stbcx.", cr);
			break;
#endif
		case 4:
			__put_user_asmx(op->val, ea, err, "stwcx.", cr);
			break;
#ifdef __powerpc64__
		case 8:
			__put_user_asmx(op->val, ea, err, "stdcx.", cr);
			break;
		case 16:
			err = do_stqcx(ea, regs->gpr[op->reg],
				       regs->gpr[op->reg + 1], &cr);
			break;
#endif
		default:
			return -EINVAL;
		}
		if (!err)
			regs->ccr = (regs->ccr & 0x0fffffff) |
				(cr & 0xe0000000) |
				((regs->xer >> 3) & 0x10000000);
		else
			regs->dar = ea;
		break;

	case LOAD:
#ifdef __powerpc64__
		if (size == 16) {
			err = emulate_lq(regs, ea, op->reg, cross_endian);
			break;
		}
#endif
		err = read_mem(&regs->gpr[op->reg], ea, size, regs);
		if (!err) {
			if (op->type & SIGNEXT)
				do_signext(&regs->gpr[op->reg], size);
			if ((op->type & BYTEREV) == (cross_endian ? 0 : BYTEREV))
				do_byterev(&regs->gpr[op->reg], size);
		}
		break;

#ifdef CONFIG_PPC_FPU
	case LOAD_FP:
		/*
		 * If the instruction is in userspace, we can emulate it even
		 * if the VMX state is not live, because we have the state
		 * stored in the thread_struct.  If the instruction is in
		 * the kernel, we must not touch the state in the thread_struct.
		 */
		if (!(regs->msr & MSR_PR) && !(regs->msr & MSR_FP))
			return 0;
		err = do_fp_load(op, ea, regs, cross_endian);
		break;
#endif
#ifdef CONFIG_ALTIVEC
	case LOAD_VMX:
		if (!(regs->msr & MSR_PR) && !(regs->msr & MSR_VEC))
			return 0;
		err = do_vec_load(op->reg, ea, size, regs, cross_endian);
		break;
#endif
#ifdef CONFIG_VSX
	case LOAD_VSX: {
		unsigned long msrbit = MSR_VSX;

		/*
		 * Some VSX instructions check the MSR_VEC bit rather than MSR_VSX
		 * when the target of the instruction is a vector register.
		 */
		if (op->reg >= 32 && (op->vsx_flags & VSX_CHECK_VEC))
			msrbit = MSR_VEC;
		if (!(regs->msr & MSR_PR) && !(regs->msr & msrbit))
			return 0;
		err = do_vsx_load(op, ea, regs, cross_endian);
		break;
	}
#endif
	case LOAD_MULTI:
		if (!address_ok(regs, ea, size))
			return -EFAULT;
		rd = op->reg;
		for (i = 0; i < size; i += 4) {
			unsigned int v32 = 0;

			nb = size - i;
			if (nb > 4)
				nb = 4;
			err = copy_mem_in((u8 *) &v32, ea, nb, regs);
			if (err)
				break;
			if (unlikely(cross_endian))
				v32 = byterev_4(v32);
			regs->gpr[rd] = v32;
			ea += 4;
			/* reg number wraps from 31 to 0 for lsw[ix] */
			rd = (rd + 1) & 0x1f;
		}
		break;

	case STORE:
#ifdef __powerpc64__
		if (size == 16) {
			err = emulate_stq(regs, ea, op->reg, cross_endian);
			break;
		}
#endif
		if ((op->type & UPDATE) && size == sizeof(long) &&
		    op->reg == 1 && op->update_reg == 1 &&
		    !(regs->msr & MSR_PR) &&
		    ea >= regs->gpr[1] - STACK_INT_FRAME_SIZE) {
			err = handle_stack_update(ea, regs);
			break;
		}
		if (unlikely(cross_endian))
			do_byterev(&op->val, size);
		err = write_mem(op->val, ea, size, regs);
		break;

#ifdef CONFIG_PPC_FPU
	case STORE_FP:
		if (!(regs->msr & MSR_PR) && !(regs->msr & MSR_FP))
			return 0;
		err = do_fp_store(op, ea, regs, cross_endian);
		break;
#endif
#ifdef CONFIG_ALTIVEC
	case STORE_VMX:
		if (!(regs->msr & MSR_PR) && !(regs->msr & MSR_VEC))
			return 0;
		err = do_vec_store(op->reg, ea, size, regs, cross_endian);
		break;
#endif
#ifdef CONFIG_VSX
	case STORE_VSX: {
		unsigned long msrbit = MSR_VSX;

		/*
		 * Some VSX instructions check the MSR_VEC bit rather than MSR_VSX
		 * when the target of the instruction is a vector register.
		 */
		if (op->reg >= 32 && (op->vsx_flags & VSX_CHECK_VEC))
			msrbit = MSR_VEC;
		if (!(regs->msr & MSR_PR) && !(regs->msr & msrbit))
			return 0;
		err = do_vsx_store(op, ea, regs, cross_endian);
		break;
	}
#endif
	case STORE_MULTI:
		if (!address_ok(regs, ea, size))
			return -EFAULT;
		rd = op->reg;
		for (i = 0; i < size; i += 4) {
			unsigned int v32 = regs->gpr[rd];

			nb = size - i;
			if (nb > 4)
				nb = 4;
			if (unlikely(cross_endian))
				v32 = byterev_4(v32);
			err = copy_mem_out((u8 *) &v32, ea, nb, regs);
			if (err)
				break;
			ea += 4;
			/* reg number wraps from 31 to 0 for stsw[ix] */
			rd = (rd + 1) & 0x1f;
		}
		break;

	default:
		return -EINVAL;
	}

	if (err)
		return err;

	if (op->type & UPDATE)
		regs->gpr[op->update_reg] = op->ea;

	return 0;
}
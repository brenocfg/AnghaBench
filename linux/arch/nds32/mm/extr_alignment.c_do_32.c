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
struct pt_regs {int ipc; } ;

/* Variables and functions */
 int EACCES ; 
 int EFAULT ; 
 int GET_IMMSVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMM (unsigned long) ; 
 int /*<<< orphan*/  RA (unsigned long) ; 
 int /*<<< orphan*/  RB (unsigned long) ; 
 int /*<<< orphan*/  RT (unsigned long) ; 
 unsigned long SV (unsigned long) ; 
 int /*<<< orphan*/  access_ok (void*,int) ; 
 int /*<<< orphan*/  get_data (unsigned long,unsigned long*,int) ; 
 unsigned long* idx_to_addr (struct pt_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_data (void*,unsigned long,int) ; 
 unsigned long sign_extend (unsigned long,int) ; 

__attribute__((used)) static inline int do_32(unsigned long inst, struct pt_regs *regs)
{
	int imm, regular, load, len, sign_ext;
	unsigned long unaligned_addr, target_val, shift;

	unaligned_addr = *idx_to_addr(regs, RA(inst));

	switch ((inst >> 25) << 1) {

	case 0x02:		/* LHI       */
		imm = 1;
		regular = 1;
		load = 1;
		len = 2;
		sign_ext = 0;
		break;
	case 0x0A:		/* LHI.bi    */
		imm = 1;
		regular = 0;
		load = 1;
		len = 2;
		sign_ext = 0;
		break;
	case 0x22:		/* LHSI      */
		imm = 1;
		regular = 1;
		load = 1;
		len = 2;
		sign_ext = 1;
		break;
	case 0x2A:		/* LHSI.bi   */
		imm = 1;
		regular = 0;
		load = 1;
		len = 2;
		sign_ext = 1;
		break;
	case 0x04:		/* LWI       */
		imm = 1;
		regular = 1;
		load = 1;
		len = 4;
		sign_ext = 0;
		break;
	case 0x0C:		/* LWI.bi    */
		imm = 1;
		regular = 0;
		load = 1;
		len = 4;
		sign_ext = 0;
		break;
	case 0x12:		/* SHI       */
		imm = 1;
		regular = 1;
		load = 0;
		len = 2;
		sign_ext = 0;
		break;
	case 0x1A:		/* SHI.bi    */
		imm = 1;
		regular = 0;
		load = 0;
		len = 2;
		sign_ext = 0;
		break;
	case 0x14:		/* SWI       */
		imm = 1;
		regular = 1;
		load = 0;
		len = 4;
		sign_ext = 0;
		break;
	case 0x1C:		/* SWI.bi    */
		imm = 1;
		regular = 0;
		load = 0;
		len = 4;
		sign_ext = 0;
		break;

	default:
		switch (inst & 0xff) {

		case 0x01:	/* LH        */
			imm = 0;
			regular = 1;
			load = 1;
			len = 2;
			sign_ext = 0;
			break;
		case 0x05:	/* LH.bi     */
			imm = 0;
			regular = 0;
			load = 1;
			len = 2;
			sign_ext = 0;
			break;
		case 0x11:	/* LHS       */
			imm = 0;
			regular = 1;
			load = 1;
			len = 2;
			sign_ext = 1;
			break;
		case 0x15:	/* LHS.bi    */
			imm = 0;
			regular = 0;
			load = 1;
			len = 2;
			sign_ext = 1;
			break;
		case 0x02:	/* LW        */
			imm = 0;
			regular = 1;
			load = 1;
			len = 4;
			sign_ext = 0;
			break;
		case 0x06:	/* LW.bi     */
			imm = 0;
			regular = 0;
			load = 1;
			len = 4;
			sign_ext = 0;
			break;
		case 0x09:	/* SH        */
			imm = 0;
			regular = 1;
			load = 0;
			len = 2;
			sign_ext = 0;
			break;
		case 0x0D:	/* SH.bi     */
			imm = 0;
			regular = 0;
			load = 0;
			len = 2;
			sign_ext = 0;
			break;
		case 0x0A:	/* SW        */
			imm = 0;
			regular = 1;
			load = 0;
			len = 4;
			sign_ext = 0;
			break;
		case 0x0E:	/* SW.bi     */
			imm = 0;
			regular = 0;
			load = 0;
			len = 4;
			sign_ext = 0;
			break;

		default:
			return -EFAULT;
		}
	}

	if (imm)
		shift = GET_IMMSVAL(IMM(inst)) * len;
	else
		shift = *idx_to_addr(regs, RB(inst)) << SV(inst);

	if (regular)
		unaligned_addr += shift;

	if (load) {

		if (!access_ok((void *)unaligned_addr, len))
			return -EACCES;

		get_data(unaligned_addr, &target_val, len);

		if (sign_ext)
			*idx_to_addr(regs, RT(inst)) =
			    sign_extend(target_val, len);
		else
			*idx_to_addr(regs, RT(inst)) = target_val;
	} else {

		if (!access_ok((void *)unaligned_addr, len))
			return -EACCES;

		target_val = *idx_to_addr(regs, RT(inst));
		set_data((void *)unaligned_addr, target_val, len);
	}

	if (!regular)
		*idx_to_addr(regs, RA(inst)) = unaligned_addr + shift;

	regs->ipc += 4;

	return 0;
fault:
	return -EACCES;
}
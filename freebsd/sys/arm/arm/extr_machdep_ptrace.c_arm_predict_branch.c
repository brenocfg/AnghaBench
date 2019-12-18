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
typedef  int register_t ;

/* Variables and functions */
 int EINVAL ; 

int
arm_predict_branch(void *cookie, u_int insn, register_t pc, register_t *new_pc,
    u_int (*fetch_reg)(void*, int),
    u_int (*read_int)(void*, vm_offset_t, u_int*))
{
	u_int addr, nregs, offset = 0;
	int error = 0;

	switch ((insn >> 24) & 0xf) {
	case 0x2:	/* add pc, reg1, #value */
	case 0x0:	/* add pc, reg1, reg2, lsl #offset */
		addr = fetch_reg(cookie, (insn >> 16) & 0xf);
		if (((insn >> 16) & 0xf) == 15)
			addr += 8;
		if (insn & 0x0200000) {
			offset = (insn >> 7) & 0x1e;
			offset = (insn & 0xff) << (32 - offset) |
			    (insn & 0xff) >> offset;
		} else {

			offset = fetch_reg(cookie, insn & 0x0f);
			if ((insn & 0x0000ff0) != 0x00000000) {
				if (insn & 0x10)
					nregs = fetch_reg(cookie,
					    (insn >> 8) & 0xf);
				else
					nregs = (insn >> 7) & 0x1f;
				switch ((insn >> 5) & 3) {
				case 0:
					/* lsl */
					offset = offset << nregs;
					break;
				case 1:
					/* lsr */
					offset = offset >> nregs;
					break;
				default:
					break; /* XXX */
				}

			}
			*new_pc = addr + offset;
			return (0);

		}

	case 0xa:	/* b ... */
	case 0xb:	/* bl ... */
		addr = ((insn << 2) & 0x03ffffff);
		if (addr & 0x02000000)
			addr |= 0xfc000000;
		*new_pc = (pc + 8 + addr);
		return (0);
	case 0x7:	/* ldr pc, [pc, reg, lsl #2] */
		addr = fetch_reg(cookie, insn & 0xf);
		addr = pc + 8 + (addr << 2);
		error = read_int(cookie, addr, &addr);
		*new_pc = addr;
		return (error);
	case 0x1:	/* mov pc, reg */
		*new_pc = fetch_reg(cookie, insn & 0xf);
		return (0);
	case 0x4:
	case 0x5:	/* ldr pc, [reg] */
		addr = fetch_reg(cookie, (insn >> 16) & 0xf);
		/* ldr pc, [reg, #offset] */
		if (insn & (1 << 24))
			offset = insn & 0xfff;
		if (insn & 0x00800000)
			addr += offset;
		else
			addr -= offset;
		error = read_int(cookie, addr, &addr);
		*new_pc = addr;

		return (error);
	case 0x8:	/* ldmxx reg, {..., pc} */
	case 0x9:
		addr = fetch_reg(cookie, (insn >> 16) & 0xf);
		nregs = (insn  & 0x5555) + ((insn  >> 1) & 0x5555);
		nregs = (nregs & 0x3333) + ((nregs >> 2) & 0x3333);
		nregs = (nregs + (nregs >> 4)) & 0x0f0f;
		nregs = (nregs + (nregs >> 8)) & 0x001f;
		switch ((insn >> 23) & 0x3) {
		case 0x0:	/* ldmda */
			addr = addr - 0;
			break;
		case 0x1:	/* ldmia */
			addr = addr + 0 + ((nregs - 1) << 2);
			break;
		case 0x2:	/* ldmdb */
			addr = addr - 4;
			break;
		case 0x3:	/* ldmib */
			addr = addr + 4 + ((nregs - 1) << 2);
			break;
		}
		error = read_int(cookie, addr, &addr);
		*new_pc = addr;

		return (error);
	default:
		return (EINVAL);
	}
}
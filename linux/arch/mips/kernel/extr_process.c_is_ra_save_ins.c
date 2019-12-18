#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int opcode; int rs; int rt; int simmediate; } ;
struct TYPE_7__ {int rd; int base; int simmediate; int /*<<< orphan*/  func; } ;
struct TYPE_6__ {int imm; int /*<<< orphan*/  rlist; int /*<<< orphan*/  func; } ;
struct TYPE_5__ {int opcode; int rt; int imm; } ;
union mips_instruction {int word; TYPE_4__ i_format; TYPE_3__ mm_m_format; TYPE_2__ mm16_m_format; TYPE_1__ mm16_r5_format; } ;
typedef  int /*<<< orphan*/  ulong ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 scalar_t__ mm_insn_16bit (int) ; 
#define  mm_pool16c_op 133 
#define  mm_pool32b_op 132 
#define  mm_sw32_op 131 
#define  mm_swm16_op 130 
#define  mm_swm32_func 129 
#define  mm_swsp16_op 128 
 int sd_op ; 
 int sw_op ; 

__attribute__((used)) static inline int is_ra_save_ins(union mips_instruction *ip, int *poff)
{
#ifdef CONFIG_CPU_MICROMIPS
	/*
	 * swsp ra,offset
	 * swm16 reglist,offset(sp)
	 * swm32 reglist,offset(sp)
	 * sw32 ra,offset(sp)
	 * jradiussp - NOT SUPPORTED
	 *
	 * microMIPS is way more fun...
	 */
	if (mm_insn_16bit(ip->word >> 16)) {
		switch (ip->mm16_r5_format.opcode) {
		case mm_swsp16_op:
			if (ip->mm16_r5_format.rt != 31)
				return 0;

			*poff = ip->mm16_r5_format.imm;
			*poff = (*poff << 2) / sizeof(ulong);
			return 1;

		case mm_pool16c_op:
			switch (ip->mm16_m_format.func) {
			case mm_swm16_op:
				*poff = ip->mm16_m_format.imm;
				*poff += 1 + ip->mm16_m_format.rlist;
				*poff = (*poff << 2) / sizeof(ulong);
				return 1;

			default:
				return 0;
			}

		default:
			return 0;
		}
	}

	switch (ip->i_format.opcode) {
	case mm_sw32_op:
		if (ip->i_format.rs != 29)
			return 0;
		if (ip->i_format.rt != 31)
			return 0;

		*poff = ip->i_format.simmediate / sizeof(ulong);
		return 1;

	case mm_pool32b_op:
		switch (ip->mm_m_format.func) {
		case mm_swm32_func:
			if (ip->mm_m_format.rd < 0x10)
				return 0;
			if (ip->mm_m_format.base != 29)
				return 0;

			*poff = ip->mm_m_format.simmediate;
			*poff += (ip->mm_m_format.rd & 0xf) * sizeof(u32);
			*poff /= sizeof(ulong);
			return 1;
		default:
			return 0;
		}

	default:
		return 0;
	}
#else
	/* sw / sd $ra, offset($sp) */
	if ((ip->i_format.opcode == sw_op || ip->i_format.opcode == sd_op) &&
		ip->i_format.rs == 29 && ip->i_format.rt == 31) {
		*poff = ip->i_format.simmediate / sizeof(ulong);
		return 1;
	}

	return 0;
#endif
}
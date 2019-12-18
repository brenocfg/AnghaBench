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
struct TYPE_8__ {scalar_t__ opcode; scalar_t__ func; } ;
struct TYPE_7__ {scalar_t__ opcode; } ;
struct TYPE_6__ {int uimmediate; } ;
struct TYPE_5__ {scalar_t__ opcode; int rt; } ;
union mips_instruction {int word; TYPE_4__ r_format; TYPE_3__ j_format; TYPE_2__ u_format; TYPE_1__ mm16_r5_format; } ;

/* Variables and functions */
 scalar_t__ j_op ; 
 scalar_t__ jal_op ; 
 scalar_t__ jalr_op ; 
 scalar_t__ jr_op ; 
 scalar_t__ mm_insn_16bit (int) ; 
 scalar_t__ mm_j32_op ; 
 scalar_t__ mm_jal32_op ; 
 int mm_jalr_op ; 
 int mm_jr16_op ; 
 scalar_t__ mm_pool16c_op ; 
 scalar_t__ mm_pool32a_op ; 
 scalar_t__ mm_pool32axf_op ; 
 scalar_t__ spec_op ; 

__attribute__((used)) static inline int is_jump_ins(union mips_instruction *ip)
{
#ifdef CONFIG_CPU_MICROMIPS
	/*
	 * jr16,jrc,jalr16,jalr16
	 * jal
	 * jalr/jr,jalr.hb/jr.hb,jalrs,jalrs.hb
	 * jraddiusp - NOT SUPPORTED
	 *
	 * microMIPS is kind of more fun...
	 */
	if (mm_insn_16bit(ip->word >> 16)) {
		if ((ip->mm16_r5_format.opcode == mm_pool16c_op &&
		    (ip->mm16_r5_format.rt & mm_jr16_op) == mm_jr16_op))
			return 1;
		return 0;
	}

	if (ip->j_format.opcode == mm_j32_op)
		return 1;
	if (ip->j_format.opcode == mm_jal32_op)
		return 1;
	if (ip->r_format.opcode != mm_pool32a_op ||
			ip->r_format.func != mm_pool32axf_op)
		return 0;
	return ((ip->u_format.uimmediate >> 6) & mm_jalr_op) == mm_jalr_op;
#else
	if (ip->j_format.opcode == j_op)
		return 1;
	if (ip->j_format.opcode == jal_op)
		return 1;
	if (ip->r_format.opcode != spec_op)
		return 0;
	return ip->r_format.func == jalr_op || ip->r_format.func == jr_op;
#endif
}
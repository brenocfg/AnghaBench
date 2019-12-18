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
struct TYPE_2__ {scalar_t__ opcode; int rs; int rt; } ;
union mips_instruction {TYPE_1__ i_format; } ;

/* Variables and functions */
 scalar_t__ sd_op ; 
 scalar_t__ sw_op ; 

__attribute__((used)) static inline int is_ra_save_ins(union mips_instruction *ip)
{
	/* sw / sd $ra, offset($sp) */
	return (ip->i_format.opcode == sw_op || ip->i_format.opcode == sd_op)
		&& ip->i_format.rs == 29 && ip->i_format.rt == 31;
}
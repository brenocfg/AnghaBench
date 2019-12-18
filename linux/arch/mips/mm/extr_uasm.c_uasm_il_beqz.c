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
typedef  int /*<<< orphan*/  u32 ;
struct uasm_reloc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  uasm_i_beqz (int /*<<< orphan*/ **,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uasm_r_mips_pc16 (struct uasm_reloc**,int /*<<< orphan*/ *,int) ; 

void uasm_il_beqz(u32 **p, struct uasm_reloc **r, unsigned int reg,
			   int lid)
{
	uasm_r_mips_pc16(r, *p, lid);
	uasm_i_beqz(p, reg, 0);
}
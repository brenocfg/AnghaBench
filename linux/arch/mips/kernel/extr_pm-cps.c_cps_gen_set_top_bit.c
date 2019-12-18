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
struct uasm_label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  t0 ; 
 int /*<<< orphan*/  t1 ; 
 int /*<<< orphan*/  uasm_build_label (struct uasm_label**,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uasm_i_ll (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  uasm_i_lui (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uasm_i_nop (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  uasm_i_or (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uasm_i_sc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  uasm_il_beqz (int /*<<< orphan*/ **,struct uasm_reloc**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uasm_rel_hi (int) ; 

__attribute__((used)) static void cps_gen_set_top_bit(u32 **pp, struct uasm_label **pl,
				struct uasm_reloc **pr,
				unsigned r_addr, int lbl)
{
	uasm_i_lui(pp, t0, uasm_rel_hi(0x80000000));
	uasm_build_label(pl, *pp, lbl);
	uasm_i_ll(pp, t1, 0, r_addr);
	uasm_i_or(pp, t1, t1, t0);
	uasm_i_sc(pp, t1, 0, r_addr);
	uasm_il_beqz(pp, pr, t1, lbl);
	uasm_i_nop(pp);
}
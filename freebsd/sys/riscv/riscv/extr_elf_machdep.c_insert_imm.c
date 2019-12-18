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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  extract_bits (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  insert_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static uint32_t
insert_imm(uint32_t insn, uint32_t imm, int imm_msb, int imm_lsb,
    int insn_lsb)
{
	int insn_msb;
	uint32_t v;

	v = extract_bits(imm, imm_msb, imm_lsb);
	insn_msb = (imm_msb - imm_lsb) + insn_lsb;

	return (insert_bits(insn, v, insn_msb, insn_lsb));
}
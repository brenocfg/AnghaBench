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
typedef  int uint8_t ;
struct pt_ild {int nominal_opcode; int max_bytes; int imm1_bytes; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTI_MAP_0 ; 
 int /*<<< orphan*/  PTI_MAP_1 ; 
 int /*<<< orphan*/  PTI_MAP_2 ; 
 int /*<<< orphan*/  PTI_MAP_3 ; 
 int /*<<< orphan*/  PTI_MAP_AMD3DNOW ; 
 int /*<<< orphan*/  PTI_MAP_INVALID ; 
 scalar_t__ bits_match (int,int,int) ; 
 int get_byte (struct pt_ild*,int) ; 
 int get_next_as_opcode (struct pt_ild*,int) ; 
 int modrm_dec (struct pt_ild*,int) ; 
 int pte_bad_insn ; 
 int pte_internal ; 

__attribute__((used)) static int opcode_dec(struct pt_ild *ild, uint8_t length)
{
	uint8_t b, m;

	if (!ild)
		return -pte_internal;

	/*no need to check max_bytes - it was checked in previous scanners */
	b = get_byte(ild, length);
	if (b != 0x0F) {	/* 1B opcodes, map 0 */
		ild->map = PTI_MAP_0;
		ild->nominal_opcode = b;

		return modrm_dec(ild, length + 1);
	}

	length++;		/* eat the 0x0F */

	if (ild->max_bytes <= length)
		return -pte_bad_insn;

	/* 0x0F opcodes MAPS 1,2,3 */
	m = get_byte(ild, length);
	if (m == 0x38) {
		ild->map = PTI_MAP_2;

		return get_next_as_opcode(ild, length + 1);
	} else if (m == 0x3A) {
		ild->map = PTI_MAP_3;
		ild->imm1_bytes = 1;

		return get_next_as_opcode(ild, length + 1);
	} else if (bits_match(m, 0xf8, 0x38)) {
		ild->map = PTI_MAP_INVALID;

		return get_next_as_opcode(ild, length + 1);
	} else if (m == 0x0F) {	/* 3dNow */
		ild->map = PTI_MAP_AMD3DNOW;
		ild->imm1_bytes = 1;
		/* real opcode is in immediate later on, but we need an
		 * opcode now. */
		ild->nominal_opcode = 0x0F;

		return modrm_dec(ild, length + 1);
	} else {	/* map 1 (simple two byte opcodes) */
		ild->nominal_opcode = m;
		ild->map = PTI_MAP_1;

		return modrm_dec(ild, length + 1);
	}
}
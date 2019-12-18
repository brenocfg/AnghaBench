#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_3__ {int vex; int rex_r; int rex_w; } ;
struct TYPE_4__ {TYPE_1__ s; } ;
struct pt_ild {scalar_t__ max_bytes; int imm1_bytes; scalar_t__ map; TYPE_2__ u; } ;

/* Variables and functions */
 scalar_t__ PTI_MAP_3 ; 
 scalar_t__ PTI_MAP_INVALID ; 
 int /*<<< orphan*/  bits_match (scalar_t__,int,int) ; 
 scalar_t__ get_byte (struct pt_ild*,scalar_t__) ; 
 int /*<<< orphan*/  mode_64b (struct pt_ild*) ; 
 int opcode_dec (struct pt_ild*,scalar_t__) ; 
 int prefix_vex_done (struct pt_ild*,scalar_t__) ; 
 int pte_bad_insn ; 
 int pte_internal ; 

__attribute__((used)) static int prefix_vex_c4(struct pt_ild *ild, uint8_t length, uint8_t rex)
{
	uint8_t max_bytes;
	uint8_t p1, p2, map;

	(void) rex;

	if (!ild)
		return -pte_internal;

	max_bytes = ild->max_bytes;

	/* Read the next byte to validate that this is indeed VEX. */
	if (max_bytes <= (length + 1))
		return -pte_bad_insn;

	p1 = get_byte(ild, length + 1);

	/* If p1[7:6] is not 11b in non-64-bit mode, this is LES, not VEX. */
	if (!mode_64b(ild) && !bits_match(p1, 0xc0, 0xc0))
		return opcode_dec(ild, length);

	/* We need at least 4 bytes
	 * - 3 for the VEX prefix and payload and
	 * - 1 for the opcode.
	 */
	if (max_bytes < (length + 4))
		return -pte_bad_insn;

	p2 = get_byte(ild, length + 2);

	ild->u.s.vex = 1;
	if (p1 & 0x80)
		ild->u.s.rex_r = 1;
	if (p2 & 0x80)
		ild->u.s.rex_w = 1;

	map = p1 & 0x1f;
	if (PTI_MAP_INVALID <= map)
		return -pte_bad_insn;

	ild->map = map;
	if (map == PTI_MAP_3)
		ild->imm1_bytes = 1;

	/* Eat the VEX. */
	length += 3;
	return prefix_vex_done(ild, length);
}
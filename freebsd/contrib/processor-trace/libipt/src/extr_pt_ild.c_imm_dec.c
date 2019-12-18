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
typedef  scalar_t__ uint8_t ;
struct pt_ild {scalar_t__ map; scalar_t__ max_bytes; scalar_t__ imm1_bytes; scalar_t__ imm2_bytes; int /*<<< orphan*/  nominal_opcode; } ;

/* Variables and functions */
 scalar_t__ PTI_MAP_AMD3DNOW ; 
 int /*<<< orphan*/  get_byte (struct pt_ild*,scalar_t__) ; 
 int pte_bad_insn ; 
 int pte_internal ; 
 int set_imm_bytes (struct pt_ild*) ; 

__attribute__((used)) static int imm_dec(struct pt_ild *ild, uint8_t length)
{
	int errcode;

	if (!ild)
		return -pte_internal;

	if (ild->map == PTI_MAP_AMD3DNOW) {
		if (ild->max_bytes <= length)
			return -pte_bad_insn;

		ild->nominal_opcode = get_byte(ild, length);
		return length + 1;
	}

	errcode = set_imm_bytes(ild);
	if (errcode < 0)
		return errcode;

	length += ild->imm1_bytes;
	length += ild->imm2_bytes;
	if (ild->max_bytes < length)
		return -pte_bad_insn;

	return length;
}
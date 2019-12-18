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
typedef  int /*<<< orphan*/  uint8_t ;
struct pt_insn_ext {int dummy; } ;
struct pt_insn {int /*<<< orphan*/  size; int /*<<< orphan*/  raw; int /*<<< orphan*/  mode; } ;
struct pt_ild {int /*<<< orphan*/  max_bytes; int /*<<< orphan*/  itext; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int pt_instruction_decode (struct pt_insn*,struct pt_insn_ext*,struct pt_ild*) ; 
 int pt_instruction_length_decode (struct pt_ild*) ; 
 int pte_internal ; 

int pt_ild_decode(struct pt_insn *insn, struct pt_insn_ext *iext)
{
	struct pt_ild ild;
	int size;

	if (!insn || !iext)
		return -pte_internal;

	ild.mode = insn->mode;
	ild.itext = insn->raw;
	ild.max_bytes = insn->size;

	size = pt_instruction_length_decode(&ild);
	if (size < 0)
		return size;

	insn->size = (uint8_t) size;

	return pt_instruction_decode(insn, iext, &ild);
}
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
typedef  scalar_t__ kprobe_opcode_t ;
typedef  int /*<<< orphan*/  insn_byte_t ;
typedef  int /*<<< orphan*/  insn_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  inat_get_opcode_attribute (int /*<<< orphan*/ ) ; 
 scalar_t__ inat_is_legacy_prefix (int /*<<< orphan*/ ) ; 
 scalar_t__ inat_is_rex_prefix (int /*<<< orphan*/ ) ; 

__attribute__((used)) static kprobe_opcode_t *skip_prefixes(kprobe_opcode_t *insn)
{
	insn_attr_t attr;

	attr = inat_get_opcode_attribute((insn_byte_t)*insn);
	while (inat_is_legacy_prefix(attr)) {
		insn++;
		attr = inat_get_opcode_attribute((insn_byte_t)*insn);
	}
#ifdef CONFIG_X86_64
	if (inat_is_rex_prefix(attr))
		insn++;
#endif
	return insn;
}
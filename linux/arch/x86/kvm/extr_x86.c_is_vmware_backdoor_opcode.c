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
struct x86_emulate_ctxt {int opcode_len; int /*<<< orphan*/  b; } ;

/* Variables and functions */

__attribute__((used)) static bool is_vmware_backdoor_opcode(struct x86_emulate_ctxt *ctxt)
{
	switch (ctxt->opcode_len) {
	case 1:
		switch (ctxt->b) {
		case 0xe4:	/* IN */
		case 0xe5:
		case 0xec:
		case 0xed:
		case 0xe6:	/* OUT */
		case 0xe7:
		case 0xee:
		case 0xef:
		case 0x6c:	/* INS */
		case 0x6d:
		case 0x6e:	/* OUTS */
		case 0x6f:
			return true;
		}
		break;
	case 2:
		switch (ctxt->b) {
		case 0x33:	/* RDPMC */
			return true;
		}
		break;
	}

	return false;
}
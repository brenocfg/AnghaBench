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
typedef  int u16 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  is_known_insn (unsigned char*) ; 

int probe_is_prohibited_opcode(u16 *insn)
{
	if (!is_known_insn((unsigned char *)insn))
		return -EINVAL;
	switch (insn[0] >> 8) {
	case 0x0c:	/* bassm */
	case 0x0b:	/* bsm	 */
	case 0x83:	/* diag  */
	case 0x44:	/* ex	 */
	case 0xac:	/* stnsm */
	case 0xad:	/* stosm */
		return -EINVAL;
	case 0xc6:
		switch (insn[0] & 0x0f) {
		case 0x00: /* exrl   */
			return -EINVAL;
		}
	}
	switch (insn[0]) {
	case 0x0101:	/* pr	 */
	case 0xb25a:	/* bsa	 */
	case 0xb240:	/* bakr  */
	case 0xb258:	/* bsg	 */
	case 0xb218:	/* pc	 */
	case 0xb228:	/* pt	 */
	case 0xb98d:	/* epsw	 */
	case 0xe560:	/* tbegin */
	case 0xe561:	/* tbeginc */
	case 0xb2f8:	/* tend	 */
		return -EINVAL;
	}
	return 0;
}
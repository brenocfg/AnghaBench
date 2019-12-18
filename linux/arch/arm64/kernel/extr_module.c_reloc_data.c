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
typedef  int /*<<< orphan*/  u64 ;
typedef  void* s64 ;
typedef  void* s32 ;
typedef  void* s16 ;
typedef  enum aarch64_reloc_op { ____Placeholder_aarch64_reloc_op } aarch64_reloc_op ;

/* Variables and functions */
 int ERANGE ; 
#define  RELOC_OP_ABS 129 
#define  RELOC_OP_PREL 128 
 void* S16_MAX ; 
 void* S16_MIN ; 
 void* S32_MAX ; 
 void* S32_MIN ; 
 void* U16_MAX ; 
 void* U32_MAX ; 
 void* do_reloc (int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int reloc_data(enum aarch64_reloc_op op, void *place, u64 val, int len)
{
	s64 sval = do_reloc(op, place, val);

	/*
	 * The ELF psABI for AArch64 documents the 16-bit and 32-bit place
	 * relative and absolute relocations as having a range of [-2^15, 2^16)
	 * or [-2^31, 2^32), respectively. However, in order to be able to
	 * detect overflows reliably, we have to choose whether we interpret
	 * such quantities as signed or as unsigned, and stick with it.
	 * The way we organize our address space requires a signed
	 * interpretation of 32-bit relative references, so let's use that
	 * for all R_AARCH64_PRELxx relocations. This means our upper
	 * bound for overflow detection should be Sxx_MAX rather than Uxx_MAX.
	 */

	switch (len) {
	case 16:
		*(s16 *)place = sval;
		switch (op) {
		case RELOC_OP_ABS:
			if (sval < 0 || sval > U16_MAX)
				return -ERANGE;
			break;
		case RELOC_OP_PREL:
			if (sval < S16_MIN || sval > S16_MAX)
				return -ERANGE;
			break;
		default:
			pr_err("Invalid 16-bit data relocation (%d)\n", op);
			return 0;
		}
		break;
	case 32:
		*(s32 *)place = sval;
		switch (op) {
		case RELOC_OP_ABS:
			if (sval < 0 || sval > U32_MAX)
				return -ERANGE;
			break;
		case RELOC_OP_PREL:
			if (sval < S32_MIN || sval > S32_MAX)
				return -ERANGE;
			break;
		default:
			pr_err("Invalid 32-bit data relocation (%d)\n", op);
			return 0;
		}
		break;
	case 64:
		*(s64 *)place = sval;
		break;
	default:
		pr_err("Invalid length (%d) for data relocation\n", len);
		return 0;
	}
	return 0;
}
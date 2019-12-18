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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct i40e_context_ele {int lsb; int width; int offset; } ;
typedef  int /*<<< orphan*/  src_dword ;
typedef  int /*<<< orphan*/  dest_dword ;
typedef  int __le32 ;

/* Variables and functions */
 int BIT (int) ; 
 int CPU_TO_LE32 (int) ; 
 int /*<<< orphan*/  I40E_DMA_TO_NONDMA ; 
 int /*<<< orphan*/  I40E_NONDMA_TO_DMA ; 
 int LE32_TO_CPU (int) ; 
 int /*<<< orphan*/  i40e_memcpy (int*,int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40e_read_dword(u8 *hmc_bits,
			    struct i40e_context_ele *ce_info,
			    u8 *dest)
{
	u32 dest_dword, mask;
	u8 *src, *target;
	u16 shift_width;
	__le32 src_dword;

	/* prepare the bits and mask */
	shift_width = ce_info->lsb % 8;

	/* if the field width is exactly 32 on an x86 machine, then the shift
	 * operation will not work because the SHL instructions count is masked
	 * to 5 bits so the shift will do nothing
	 */
	if (ce_info->width < 32)
		mask = BIT(ce_info->width) - 1;
	else
		mask = ~(u32)0;

	/* shift to correct alignment */
	mask <<= shift_width;

	/* get the current bits from the src bit string */
	src = hmc_bits + (ce_info->lsb / 8);

	i40e_memcpy(&src_dword, src, sizeof(src_dword), I40E_DMA_TO_NONDMA);

	/* the data in the memory is stored as little endian so mask it
	 * correctly
	 */
	src_dword &= ~(CPU_TO_LE32(mask));

	/* get the data back into host order before shifting */
	dest_dword = LE32_TO_CPU(src_dword);

	dest_dword >>= shift_width;

	/* get the address from the struct field */
	target = dest + ce_info->offset;

	/* put it back in the struct */
	i40e_memcpy(target, &dest_dword, sizeof(dest_dword),
		    I40E_NONDMA_TO_DMA);
}
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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct i40e_context_ele {int offset; int lsb; int width; } ;
typedef  int /*<<< orphan*/  dest_dword ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  CPU_TO_LE32 (int) ; 
 int /*<<< orphan*/  I40E_DMA_TO_NONDMA ; 
 int /*<<< orphan*/  I40E_NONDMA_TO_DMA ; 
 int /*<<< orphan*/  i40e_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40e_write_dword(u8 *hmc_bits,
			     struct i40e_context_ele *ce_info,
			     u8 *src)
{
	u32 src_dword, mask;
	u8 *from, *dest;
	u16 shift_width;
	__le32 dest_dword;

	/* copy from the next struct field */
	from = src + ce_info->offset;

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

	/* don't swizzle the bits until after the mask because the mask bits
	 * will be in a different bit position on big endian machines
	 */
	src_dword = *(u32 *)from;
	src_dword &= mask;

	/* shift to correct alignment */
	mask <<= shift_width;
	src_dword <<= shift_width;

	/* get the current bits from the target bit string */
	dest = hmc_bits + (ce_info->lsb / 8);

	i40e_memcpy(&dest_dword, dest, sizeof(dest_dword), I40E_DMA_TO_NONDMA);

	dest_dword &= ~(CPU_TO_LE32(mask));	/* get the bits not changing */
	dest_dword |= CPU_TO_LE32(src_dword);	/* add in the new bits */

	/* put it all back */
	i40e_memcpy(dest, &dest_dword, sizeof(dest_dword), I40E_NONDMA_TO_DMA);
}
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
typedef  int u16 ;
struct i40e_context_ele {int lsb; int offset; int /*<<< orphan*/  width; } ;
typedef  int /*<<< orphan*/  dest_byte ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_DMA_TO_NONDMA ; 
 int /*<<< orphan*/  I40E_NONDMA_TO_DMA ; 
 int /*<<< orphan*/  i40e_memcpy (int*,int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40e_read_byte(u8 *hmc_bits,
			   struct i40e_context_ele *ce_info,
			   u8 *dest)
{
	u8 dest_byte, mask;
	u8 *src, *target;
	u16 shift_width;

	/* prepare the bits and mask */
	shift_width = ce_info->lsb % 8;
	mask = (u8)(BIT(ce_info->width) - 1);

	/* shift to correct alignment */
	mask <<= shift_width;

	/* get the current bits from the src bit string */
	src = hmc_bits + (ce_info->lsb / 8);

	i40e_memcpy(&dest_byte, src, sizeof(dest_byte), I40E_DMA_TO_NONDMA);

	dest_byte &= ~(mask);

	dest_byte >>= shift_width;

	/* get the address from the struct field */
	target = dest + ce_info->offset;

	/* put it back in the struct */
	i40e_memcpy(target, &dest_byte, sizeof(dest_byte), I40E_NONDMA_TO_DMA);
}
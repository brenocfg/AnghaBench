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
struct i40e_context_ele {int offset; int lsb; int /*<<< orphan*/  width; } ;
typedef  int /*<<< orphan*/  dest_byte ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_DMA_TO_NONDMA ; 
 int /*<<< orphan*/  I40E_NONDMA_TO_DMA ; 
 int /*<<< orphan*/  i40e_memcpy (int*,int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40e_write_byte(u8 *hmc_bits,
			    struct i40e_context_ele *ce_info,
			    u8 *src)
{
	u8 src_byte, dest_byte, mask;
	u8 *from, *dest;
	u16 shift_width;

	/* copy from the next struct field */
	from = src + ce_info->offset;

	/* prepare the bits and mask */
	shift_width = ce_info->lsb % 8;
	mask = (u8)(BIT(ce_info->width) - 1);

	src_byte = *from;
	src_byte &= mask;

	/* shift to correct alignment */
	mask <<= shift_width;
	src_byte <<= shift_width;

	/* get the current bits from the target bit string */
	dest = hmc_bits + (ce_info->lsb / 8);

	i40e_memcpy(&dest_byte, dest, sizeof(dest_byte), I40E_DMA_TO_NONDMA);

	dest_byte &= ~mask;	/* get the bits not changing */
	dest_byte |= src_byte;	/* add in the new bits */

	/* put it all back */
	i40e_memcpy(dest, &dest_byte, sizeof(dest_byte), I40E_NONDMA_TO_DMA);
}
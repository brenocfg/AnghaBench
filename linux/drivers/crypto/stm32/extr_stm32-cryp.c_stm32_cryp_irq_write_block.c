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
typedef  int /*<<< orphan*/  u32 ;
struct stm32_cryp {size_t authsize; int hw_blocksize; size_t total_in; int /*<<< orphan*/  in_sg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYP_DIN ; 
 int _walked_in ; 
 scalar_t__ is_ccm (struct stm32_cryp*) ; 
 scalar_t__ is_decrypt (struct stm32_cryp*) ; 
 scalar_t__ is_gcm (struct stm32_cryp*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * sg_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stm32_cryp_next_in (struct stm32_cryp*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stm32_cryp_write (struct stm32_cryp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stm32_cryp_irq_write_block(struct stm32_cryp *cryp)
{
	unsigned int i, j;
	u32 *src;
	u8 d8[4];
	size_t tag_size;

	/* Do no write tag (if any) */
	if (is_decrypt(cryp) && (is_gcm(cryp) || is_ccm(cryp)))
		tag_size = cryp->authsize;
	else
		tag_size = 0;

	src = sg_virt(cryp->in_sg) + _walked_in;

	for (i = 0; i < cryp->hw_blocksize / sizeof(u32); i++) {
		if (likely(cryp->total_in - tag_size >= sizeof(u32))) {
			/* Write a full u32 */
			stm32_cryp_write(cryp, CRYP_DIN, *src);

			src = stm32_cryp_next_in(cryp, src, sizeof(u32));
			cryp->total_in -= sizeof(u32);
		} else if (cryp->total_in == tag_size) {
			/* Write padding data */
			stm32_cryp_write(cryp, CRYP_DIN, 0);
		} else {
			/* Write less than an u32 */
			memset(d8, 0, sizeof(u32));
			for (j = 0; j < cryp->total_in - tag_size; j++) {
				d8[j] = *((u8 *)src);
				src = stm32_cryp_next_in(cryp, src, 1);
			}

			stm32_cryp_write(cryp, CRYP_DIN, *(u32 *)d8);
			cryp->total_in = tag_size;
		}
	}
}
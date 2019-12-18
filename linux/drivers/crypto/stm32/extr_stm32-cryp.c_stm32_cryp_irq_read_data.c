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
struct stm32_cryp {size_t authsize; int hw_blocksize; size_t total_out; int /*<<< orphan*/  total_in; int /*<<< orphan*/  out_sg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYP_DOUT ; 
 int _walked_out ; 
 scalar_t__ is_ccm (struct stm32_cryp*) ; 
 scalar_t__ is_encrypt (struct stm32_cryp*) ; 
 scalar_t__ is_gcm (struct stm32_cryp*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/ * sg_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stm32_cryp_next_out (struct stm32_cryp*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stm32_cryp_read (struct stm32_cryp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool stm32_cryp_irq_read_data(struct stm32_cryp *cryp)
{
	unsigned int i, j;
	u32 d32, *dst;
	u8 *d8;
	size_t tag_size;

	/* Do no read tag now (if any) */
	if (is_encrypt(cryp) && (is_gcm(cryp) || is_ccm(cryp)))
		tag_size = cryp->authsize;
	else
		tag_size = 0;

	dst = sg_virt(cryp->out_sg) + _walked_out;

	for (i = 0; i < cryp->hw_blocksize / sizeof(u32); i++) {
		if (likely(cryp->total_out - tag_size >= sizeof(u32))) {
			/* Read a full u32 */
			*dst = stm32_cryp_read(cryp, CRYP_DOUT);

			dst = stm32_cryp_next_out(cryp, dst, sizeof(u32));
			cryp->total_out -= sizeof(u32);
		} else if (cryp->total_out == tag_size) {
			/* Empty fifo out (data from input padding) */
			d32 = stm32_cryp_read(cryp, CRYP_DOUT);
		} else {
			/* Read less than an u32 */
			d32 = stm32_cryp_read(cryp, CRYP_DOUT);
			d8 = (u8 *)&d32;

			for (j = 0; j < cryp->total_out - tag_size; j++) {
				*((u8 *)dst) = *(d8++);
				dst = stm32_cryp_next_out(cryp, dst, 1);
			}
			cryp->total_out = tag_size;
		}
	}

	return !(cryp->total_out - tag_size) || !cryp->total_in;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stm32_cryp {scalar_t__ total_in; scalar_t__ authsize; TYPE_1__* caps; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ padding_wa; } ;

/* Variables and functions */
 scalar_t__ AES_BLOCK_SIZE ; 
 scalar_t__ CR_AES_CCM ; 
 scalar_t__ CR_AES_GCM ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ is_aes (struct stm32_cryp*) ; 
 scalar_t__ is_ctr (struct stm32_cryp*) ; 
 scalar_t__ is_decrypt (struct stm32_cryp*) ; 
 scalar_t__ is_encrypt (struct stm32_cryp*) ; 
 int /*<<< orphan*/  stm32_cryp_check_ctr_counter (struct stm32_cryp*) ; 
 scalar_t__ stm32_cryp_get_hw_mode (struct stm32_cryp*) ; 
 int /*<<< orphan*/  stm32_cryp_irq_set_npblb (struct stm32_cryp*) ; 
 int /*<<< orphan*/  stm32_cryp_irq_write_block (struct stm32_cryp*) ; 
 void stm32_cryp_irq_write_ccm_padded_data (struct stm32_cryp*) ; 
 void stm32_cryp_irq_write_gcm_padded_data (struct stm32_cryp*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void stm32_cryp_irq_write_data(struct stm32_cryp *cryp)
{
	if (unlikely(!cryp->total_in)) {
		dev_warn(cryp->dev, "No more data to process\n");
		return;
	}

	if (unlikely(cryp->total_in < AES_BLOCK_SIZE &&
		     (stm32_cryp_get_hw_mode(cryp) == CR_AES_GCM) &&
		     is_encrypt(cryp))) {
		/* Padding for AES GCM encryption */
		if (cryp->caps->padding_wa)
			/* Special case 1 */
			return stm32_cryp_irq_write_gcm_padded_data(cryp);

		/* Setting padding bytes (NBBLB) */
		stm32_cryp_irq_set_npblb(cryp);
	}

	if (unlikely((cryp->total_in - cryp->authsize < AES_BLOCK_SIZE) &&
		     (stm32_cryp_get_hw_mode(cryp) == CR_AES_CCM) &&
		     is_decrypt(cryp))) {
		/* Padding for AES CCM decryption */
		if (cryp->caps->padding_wa)
			/* Special case 2 */
			return stm32_cryp_irq_write_ccm_padded_data(cryp);

		/* Setting padding bytes (NBBLB) */
		stm32_cryp_irq_set_npblb(cryp);
	}

	if (is_aes(cryp) && is_ctr(cryp))
		stm32_cryp_check_ctr_counter(cryp);

	stm32_cryp_irq_write_block(cryp);
}
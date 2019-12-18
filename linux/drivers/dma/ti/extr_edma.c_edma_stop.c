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
struct edma_chan {int /*<<< orphan*/  ch_num; struct edma_cc* ecc; } ;
struct edma_cc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EDMA_CHANNEL_BIT (int) ; 
 int EDMA_CHAN_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDMA_EMCR ; 
 int EDMA_REG_ARRAY_INDEX (int) ; 
 int /*<<< orphan*/  SH_ECR ; 
 int /*<<< orphan*/  SH_EECR ; 
 int /*<<< orphan*/  SH_EER ; 
 int /*<<< orphan*/  SH_ICR ; 
 int /*<<< orphan*/  SH_SECR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edma_shadow0_read_array (struct edma_cc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  edma_shadow0_write_array (struct edma_cc*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  edma_write_array (struct edma_cc*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void edma_stop(struct edma_chan *echan)
{
	struct edma_cc *ecc = echan->ecc;
	int channel = EDMA_CHAN_SLOT(echan->ch_num);
	int idx = EDMA_REG_ARRAY_INDEX(channel);
	int ch_bit = EDMA_CHANNEL_BIT(channel);

	edma_shadow0_write_array(ecc, SH_EECR, idx, ch_bit);
	edma_shadow0_write_array(ecc, SH_ECR, idx, ch_bit);
	edma_shadow0_write_array(ecc, SH_SECR, idx, ch_bit);
	edma_write_array(ecc, EDMA_EMCR, idx, ch_bit);

	/* clear possibly pending completion interrupt */
	edma_shadow0_write_array(ecc, SH_ICR, idx, ch_bit);

	dev_dbg(ecc->dev, "EER%d %08x\n", idx,
		edma_shadow0_read_array(ecc, SH_EER, idx));

	/* REVISIT:  consider guarding against inappropriate event
	 * chaining by overwriting with dummy_paramset.
	 */
}
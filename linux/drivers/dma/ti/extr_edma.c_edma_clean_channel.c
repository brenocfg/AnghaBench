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
 int BIT (int) ; 
 int /*<<< orphan*/  EDMA_CCERRCLR ; 
 int EDMA_CHANNEL_BIT (int) ; 
 int EDMA_CHAN_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDMA_EMCR ; 
 int /*<<< orphan*/  EDMA_EMR ; 
 int EDMA_REG_ARRAY_INDEX (int) ; 
 int /*<<< orphan*/  SH_ECR ; 
 int /*<<< orphan*/  SH_SECR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edma_read_array (struct edma_cc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  edma_shadow0_write_array (struct edma_cc*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  edma_write (struct edma_cc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  edma_write_array (struct edma_cc*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void edma_clean_channel(struct edma_chan *echan)
{
	struct edma_cc *ecc = echan->ecc;
	int channel = EDMA_CHAN_SLOT(echan->ch_num);
	int idx = EDMA_REG_ARRAY_INDEX(channel);
	int ch_bit = EDMA_CHANNEL_BIT(channel);

	dev_dbg(ecc->dev, "EMR%d %08x\n", idx,
		edma_read_array(ecc, EDMA_EMR, idx));
	edma_shadow0_write_array(ecc, SH_ECR, idx, ch_bit);
	/* Clear the corresponding EMR bits */
	edma_write_array(ecc, EDMA_EMCR, idx, ch_bit);
	/* Clear any SER */
	edma_shadow0_write_array(ecc, SH_SECR, idx, ch_bit);
	edma_write(ecc, EDMA_CCERRCLR, BIT(16) | BIT(1) | BIT(0));
}
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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  tmp ;
struct stm32_cryp {size_t total_in; size_t total_out; int /*<<< orphan*/  dev; scalar_t__ total_out_save; int /*<<< orphan*/  flags; struct scatterlist* out_sg; } ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int AES_BLOCK_32 ; 
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ CRYP_CR ; 
 scalar_t__ CRYP_CSGCMCCM0R ; 
 scalar_t__ CRYP_DIN ; 
 scalar_t__ CRYP_IMSCR ; 
 scalar_t__ CRYP_IV1RR ; 
 int /*<<< orphan*/  CR_AES_CCM ; 
 int /*<<< orphan*/  CR_AES_CTR ; 
 int /*<<< orphan*/  CR_ALGO_MASK ; 
 int /*<<< orphan*/  CR_CRYPEN ; 
 int /*<<< orphan*/  CR_PH_HEADER ; 
 int /*<<< orphan*/  CR_PH_MASK ; 
 int /*<<< orphan*/  FLG_CCM_PADDED_WA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (int /*<<< orphan*/ *,struct scatterlist*,scalar_t__,size_t,int /*<<< orphan*/ ) ; 
 void stm32_cryp_finish_req (struct stm32_cryp*,int) ; 
 int /*<<< orphan*/  stm32_cryp_irq_read_data (struct stm32_cryp*) ; 
 int /*<<< orphan*/  stm32_cryp_irq_write_block (struct stm32_cryp*) ; 
 int /*<<< orphan*/  stm32_cryp_read (struct stm32_cryp*,scalar_t__) ; 
 int stm32_cryp_wait_busy (struct stm32_cryp*) ; 
 int stm32_cryp_wait_output (struct stm32_cryp*) ; 
 int /*<<< orphan*/  stm32_cryp_write (struct stm32_cryp*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stm32_cryp_irq_write_ccm_padded_data(struct stm32_cryp *cryp)
{
	int err = 0;
	u32 cfg, iv1tmp;
	u32 cstmp1[AES_BLOCK_32], cstmp2[AES_BLOCK_32], tmp[AES_BLOCK_32];
	size_t last_total_out, total_in_ori = cryp->total_in;
	struct scatterlist *out_sg_ori = cryp->out_sg;
	unsigned int i;

	/* 'Special workaround' procedure described in the datasheet */
	cryp->flags |= FLG_CCM_PADDED_WA;

	/* a) disable ip */
	stm32_cryp_write(cryp, CRYP_IMSCR, 0);

	cfg = stm32_cryp_read(cryp, CRYP_CR);
	cfg &= ~CR_CRYPEN;
	stm32_cryp_write(cryp, CRYP_CR, cfg);

	/* b) get IV1 from CRYP_CSGCMCCM7 */
	iv1tmp = stm32_cryp_read(cryp, CRYP_CSGCMCCM0R + 7 * 4);

	/* c) Load CRYP_CSGCMCCMxR */
	for (i = 0; i < ARRAY_SIZE(cstmp1); i++)
		cstmp1[i] = stm32_cryp_read(cryp, CRYP_CSGCMCCM0R + i * 4);

	/* d) Write IV1R */
	stm32_cryp_write(cryp, CRYP_IV1RR, iv1tmp);

	/* e) change mode to CTR */
	cfg &= ~CR_ALGO_MASK;
	cfg |= CR_AES_CTR;
	stm32_cryp_write(cryp, CRYP_CR, cfg);

	/* a) enable IP */
	cfg |= CR_CRYPEN;
	stm32_cryp_write(cryp, CRYP_CR, cfg);

	/* b) pad and write the last block */
	stm32_cryp_irq_write_block(cryp);
	cryp->total_in = total_in_ori;
	err = stm32_cryp_wait_output(cryp);
	if (err) {
		dev_err(cryp->dev, "Timeout (wite ccm padded data)\n");
		return stm32_cryp_finish_req(cryp, err);
	}

	/* c) get and store decrypted data */
	last_total_out = cryp->total_out;
	stm32_cryp_irq_read_data(cryp);

	memset(tmp, 0, sizeof(tmp));
	scatterwalk_map_and_copy(tmp, out_sg_ori,
				 cryp->total_out_save - last_total_out,
				 last_total_out, 0);

	/* d) Load again CRYP_CSGCMCCMxR */
	for (i = 0; i < ARRAY_SIZE(cstmp2); i++)
		cstmp2[i] = stm32_cryp_read(cryp, CRYP_CSGCMCCM0R + i * 4);

	/* e) change mode back to AES CCM */
	cfg &= ~CR_ALGO_MASK;
	cfg |= CR_AES_CCM;
	stm32_cryp_write(cryp, CRYP_CR, cfg);

	/* f) change phase to header */
	cfg &= ~CR_PH_MASK;
	cfg |= CR_PH_HEADER;
	stm32_cryp_write(cryp, CRYP_CR, cfg);

	/* g) XOR and write padded data */
	for (i = 0; i < ARRAY_SIZE(tmp); i++) {
		tmp[i] ^= cstmp1[i];
		tmp[i] ^= cstmp2[i];
		stm32_cryp_write(cryp, CRYP_DIN, tmp[i]);
	}

	/* h) wait for completion */
	err = stm32_cryp_wait_busy(cryp);
	if (err)
		dev_err(cryp->dev, "Timeout (wite ccm padded data)\n");

	/* i) run the he normal Final phase */
	stm32_cryp_finish_req(cryp, err);
}
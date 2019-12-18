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
typedef  int u32 ;
struct talitos_private {int num_channels; TYPE_1__* chan; } ;
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ reg; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int EIO ; 
 int TALITOS1_ISR_4CHERR ; 
 int TALITOS1_ISR_TEA_ERR ; 
 int TALITOS2_CCCR_CONT ; 
 int TALITOS2_ISR_4CHERR ; 
 scalar_t__ TALITOS_CCCR ; 
 scalar_t__ TALITOS_CCCR_LO ; 
 scalar_t__ TALITOS_CCPSR_LO ; 
 int TALITOS_CCPSR_LO_DOF ; 
 int TALITOS_CCPSR_LO_EU ; 
 int TALITOS_CCPSR_LO_FPZ ; 
 int TALITOS_CCPSR_LO_GB ; 
 int TALITOS_CCPSR_LO_GRL ; 
 int TALITOS_CCPSR_LO_IDH ; 
 int TALITOS_CCPSR_LO_IEU ; 
 int TALITOS_CCPSR_LO_MDTE ; 
 int TALITOS_CCPSR_LO_SB ; 
 int TALITOS_CCPSR_LO_SGDLZ ; 
 int TALITOS_CCPSR_LO_SOF ; 
 int TALITOS_CCPSR_LO_SRL ; 
 unsigned int TALITOS_TIMEOUT ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  current_desc_hdr (struct device*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct talitos_private* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  flush_channel (struct device*,int,int,int) ; 
 int has_ftr_sec1 (struct talitos_private*) ; 
 int in_be32 (scalar_t__) ; 
 int /*<<< orphan*/  init_device (struct device*) ; 
 int /*<<< orphan*/  report_eu_error (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_channel (struct device*,int) ; 
 int /*<<< orphan*/  setbits32 (scalar_t__,int) ; 

__attribute__((used)) static void talitos_error(struct device *dev, u32 isr, u32 isr_lo)
{
	struct talitos_private *priv = dev_get_drvdata(dev);
	unsigned int timeout = TALITOS_TIMEOUT;
	int ch, error, reset_dev = 0;
	u32 v_lo;
	bool is_sec1 = has_ftr_sec1(priv);
	int reset_ch = is_sec1 ? 1 : 0; /* only SEC2 supports continuation */

	for (ch = 0; ch < priv->num_channels; ch++) {
		/* skip channels without errors */
		if (is_sec1) {
			/* bits 29, 31, 17, 19 */
			if (!(isr & (1 << (29 + (ch & 1) * 2 - (ch & 2) * 6))))
				continue;
		} else {
			if (!(isr & (1 << (ch * 2 + 1))))
				continue;
		}

		error = -EINVAL;

		v_lo = in_be32(priv->chan[ch].reg + TALITOS_CCPSR_LO);

		if (v_lo & TALITOS_CCPSR_LO_DOF) {
			dev_err(dev, "double fetch fifo overflow error\n");
			error = -EAGAIN;
			reset_ch = 1;
		}
		if (v_lo & TALITOS_CCPSR_LO_SOF) {
			/* h/w dropped descriptor */
			dev_err(dev, "single fetch fifo overflow error\n");
			error = -EAGAIN;
		}
		if (v_lo & TALITOS_CCPSR_LO_MDTE)
			dev_err(dev, "master data transfer error\n");
		if (v_lo & TALITOS_CCPSR_LO_SGDLZ)
			dev_err(dev, is_sec1 ? "pointer not complete error\n"
					     : "s/g data length zero error\n");
		if (v_lo & TALITOS_CCPSR_LO_FPZ)
			dev_err(dev, is_sec1 ? "parity error\n"
					     : "fetch pointer zero error\n");
		if (v_lo & TALITOS_CCPSR_LO_IDH)
			dev_err(dev, "illegal descriptor header error\n");
		if (v_lo & TALITOS_CCPSR_LO_IEU)
			dev_err(dev, is_sec1 ? "static assignment error\n"
					     : "invalid exec unit error\n");
		if (v_lo & TALITOS_CCPSR_LO_EU)
			report_eu_error(dev, ch, current_desc_hdr(dev, ch));
		if (!is_sec1) {
			if (v_lo & TALITOS_CCPSR_LO_GB)
				dev_err(dev, "gather boundary error\n");
			if (v_lo & TALITOS_CCPSR_LO_GRL)
				dev_err(dev, "gather return/length error\n");
			if (v_lo & TALITOS_CCPSR_LO_SB)
				dev_err(dev, "scatter boundary error\n");
			if (v_lo & TALITOS_CCPSR_LO_SRL)
				dev_err(dev, "scatter return/length error\n");
		}

		flush_channel(dev, ch, error, reset_ch);

		if (reset_ch) {
			reset_channel(dev, ch);
		} else {
			setbits32(priv->chan[ch].reg + TALITOS_CCCR,
				  TALITOS2_CCCR_CONT);
			setbits32(priv->chan[ch].reg + TALITOS_CCCR_LO, 0);
			while ((in_be32(priv->chan[ch].reg + TALITOS_CCCR) &
			       TALITOS2_CCCR_CONT) && --timeout)
				cpu_relax();
			if (timeout == 0) {
				dev_err(dev, "failed to restart channel %d\n",
					ch);
				reset_dev = 1;
			}
		}
	}
	if (reset_dev || (is_sec1 && isr & ~TALITOS1_ISR_4CHERR) ||
	    (!is_sec1 && isr & ~TALITOS2_ISR_4CHERR) || isr_lo) {
		if (is_sec1 && (isr_lo & TALITOS1_ISR_TEA_ERR))
			dev_err(dev, "TEA error: ISR 0x%08x_%08x\n",
				isr, isr_lo);
		else
			dev_err(dev, "done overflow, internal time out, or "
				"rngu error: ISR 0x%08x_%08x\n", isr, isr_lo);

		/* purge request queues */
		for (ch = 0; ch < priv->num_channels; ch++)
			flush_channel(dev, ch, -EIO, 1);

		/* reset and reinitialize the device */
		init_device(dev);
	}
}
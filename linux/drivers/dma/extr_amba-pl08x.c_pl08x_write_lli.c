#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pl08x_phy_chan {int /*<<< orphan*/  reg_config; scalar_t__ base; scalar_t__ reg_control; scalar_t__ ftdmac020; scalar_t__ reg_lli; scalar_t__ reg_dst; scalar_t__ reg_src; int /*<<< orphan*/  id; } ;
struct pl08x_driver_data {TYPE_3__* vd; TYPE_2__* pd; TYPE_1__* adev; } ;
struct TYPE_6__ {scalar_t__ pl080s; } ;
struct TYPE_5__ {int memcpy_burst_size; scalar_t__ memcpy_prot_cache; scalar_t__ memcpy_prot_buff; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int FTDMAC020_CH_CSR_DSTAD_CTL_SHIFT ; 
 int FTDMAC020_CH_CSR_DST_SEL ; 
 int FTDMAC020_CH_CSR_DST_WIDTH_SHIFT ; 
 int FTDMAC020_CH_CSR_PROT1 ; 
 int FTDMAC020_CH_CSR_PROT2 ; 
 int FTDMAC020_CH_CSR_PROT3 ; 
 int FTDMAC020_CH_CSR_SRCAD_CTL_SHIFT ; 
 int FTDMAC020_CH_CSR_SRC_SEL ; 
 int FTDMAC020_CH_CSR_SRC_SIZE_SHIFT ; 
 int FTDMAC020_CH_CSR_SRC_WIDTH_SHIFT ; 
 int FTDMAC020_CH_CSR_TC_MSK ; 
 scalar_t__ FTDMAC020_CH_SIZE ; 
 int FTDMAC020_LLI_DSTAD_CTL_MSK ; 
 int FTDMAC020_LLI_DSTAD_CTL_SHIFT ; 
 int FTDMAC020_LLI_DST_SEL ; 
 int FTDMAC020_LLI_DST_WIDTH_MSK ; 
 int FTDMAC020_LLI_DST_WIDTH_SHIFT ; 
 int FTDMAC020_LLI_SRCAD_CTL_MSK ; 
 int FTDMAC020_LLI_SRCAD_CTL_SHIFT ; 
 int FTDMAC020_LLI_SRC_SEL ; 
 int FTDMAC020_LLI_SRC_WIDTH_MSK ; 
 int FTDMAC020_LLI_SRC_WIDTH_SHIFT ; 
 int FTDMAC020_LLI_TC_MSK ; 
 int FTDMAC020_LLI_TRANSFER_SIZE_MASK ; 
 scalar_t__ PL080S_CH_CONTROL2 ; 
 size_t PL080S_LLI_CCTL2 ; 
 int PL080_BSIZE_1 ; 
 int PL080_BSIZE_128 ; 
 int PL080_BSIZE_16 ; 
 int PL080_BSIZE_256 ; 
 int PL080_BSIZE_32 ; 
 int PL080_BSIZE_4 ; 
 int PL080_BSIZE_64 ; 
 int PL080_BSIZE_8 ; 
 size_t PL080_LLI_CCTL ; 
 size_t PL080_LLI_DST ; 
 size_t PL080_LLI_LLI ; 
 size_t PL080_LLI_SRC ; 
#define  PL08X_BURST_SZ_1 135 
#define  PL08X_BURST_SZ_128 134 
#define  PL08X_BURST_SZ_16 133 
#define  PL08X_BURST_SZ_256 132 
#define  PL08X_BURST_SZ_32 131 
#define  PL08X_BURST_SZ_4 130 
#define  PL08X_BURST_SZ_64 129 
#define  PL08X_BURST_SZ_8 128 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int const,int const,int const,int const,int const,...) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int const,scalar_t__) ; 

__attribute__((used)) static void pl08x_write_lli(struct pl08x_driver_data *pl08x,
		struct pl08x_phy_chan *phychan, const u32 *lli, u32 ccfg)
{
	if (pl08x->vd->pl080s)
		dev_vdbg(&pl08x->adev->dev,
			"WRITE channel %d: csrc=0x%08x, cdst=0x%08x, "
			"clli=0x%08x, cctl=0x%08x, cctl2=0x%08x, ccfg=0x%08x\n",
			phychan->id, lli[PL080_LLI_SRC], lli[PL080_LLI_DST],
			lli[PL080_LLI_LLI], lli[PL080_LLI_CCTL],
			lli[PL080S_LLI_CCTL2], ccfg);
	else
		dev_vdbg(&pl08x->adev->dev,
			"WRITE channel %d: csrc=0x%08x, cdst=0x%08x, "
			"clli=0x%08x, cctl=0x%08x, ccfg=0x%08x\n",
			phychan->id, lli[PL080_LLI_SRC], lli[PL080_LLI_DST],
			lli[PL080_LLI_LLI], lli[PL080_LLI_CCTL], ccfg);

	writel_relaxed(lli[PL080_LLI_SRC], phychan->reg_src);
	writel_relaxed(lli[PL080_LLI_DST], phychan->reg_dst);
	writel_relaxed(lli[PL080_LLI_LLI], phychan->reg_lli);

	/*
	 * The FTMAC020 has a different layout in the CCTL word of the LLI
	 * and the CCTL register which is split in CSR and SIZE registers.
	 * Convert the LLI item CCTL into the proper values to write into
	 * the CSR and SIZE registers.
	 */
	if (phychan->ftdmac020) {
		u32 llictl = lli[PL080_LLI_CCTL];
		u32 val = 0;

		/* Write the transfer size (12 bits) to the size register */
		writel_relaxed(llictl & FTDMAC020_LLI_TRANSFER_SIZE_MASK,
			       phychan->base + FTDMAC020_CH_SIZE);
		/*
		 * Then write the control bits 28..16 to the control register
		 * by shuffleing the bits around to where they are in the
		 * main register. The mapping is as follows:
		 * Bit 28: TC_MSK - mask on all except last LLI
		 * Bit 27..25: SRC_WIDTH
		 * Bit 24..22: DST_WIDTH
		 * Bit 21..20: SRCAD_CTRL
		 * Bit 19..17: DSTAD_CTRL
		 * Bit 17: SRC_SEL
		 * Bit 16: DST_SEL
		 */
		if (llictl & FTDMAC020_LLI_TC_MSK)
			val |= FTDMAC020_CH_CSR_TC_MSK;
		val |= ((llictl  & FTDMAC020_LLI_SRC_WIDTH_MSK) >>
			(FTDMAC020_LLI_SRC_WIDTH_SHIFT -
			 FTDMAC020_CH_CSR_SRC_WIDTH_SHIFT));
		val |= ((llictl  & FTDMAC020_LLI_DST_WIDTH_MSK) >>
			(FTDMAC020_LLI_DST_WIDTH_SHIFT -
			 FTDMAC020_CH_CSR_DST_WIDTH_SHIFT));
		val |= ((llictl  & FTDMAC020_LLI_SRCAD_CTL_MSK) >>
			(FTDMAC020_LLI_SRCAD_CTL_SHIFT -
			 FTDMAC020_CH_CSR_SRCAD_CTL_SHIFT));
		val |= ((llictl  & FTDMAC020_LLI_DSTAD_CTL_MSK) >>
			(FTDMAC020_LLI_DSTAD_CTL_SHIFT -
			 FTDMAC020_CH_CSR_DSTAD_CTL_SHIFT));
		if (llictl & FTDMAC020_LLI_SRC_SEL)
			val |= FTDMAC020_CH_CSR_SRC_SEL;
		if (llictl & FTDMAC020_LLI_DST_SEL)
			val |= FTDMAC020_CH_CSR_DST_SEL;

		/*
		 * Set up the bits that exist in the CSR but are not
		 * part the LLI, i.e. only gets written to the control
		 * register right here.
		 *
		 * FIXME: do not just handle memcpy, also handle slave DMA.
		 */
		switch (pl08x->pd->memcpy_burst_size) {
		default:
		case PL08X_BURST_SZ_1:
			val |= PL080_BSIZE_1 <<
				FTDMAC020_CH_CSR_SRC_SIZE_SHIFT;
			break;
		case PL08X_BURST_SZ_4:
			val |= PL080_BSIZE_4 <<
				FTDMAC020_CH_CSR_SRC_SIZE_SHIFT;
			break;
		case PL08X_BURST_SZ_8:
			val |= PL080_BSIZE_8 <<
				FTDMAC020_CH_CSR_SRC_SIZE_SHIFT;
			break;
		case PL08X_BURST_SZ_16:
			val |= PL080_BSIZE_16 <<
				FTDMAC020_CH_CSR_SRC_SIZE_SHIFT;
			break;
		case PL08X_BURST_SZ_32:
			val |= PL080_BSIZE_32 <<
				FTDMAC020_CH_CSR_SRC_SIZE_SHIFT;
			break;
		case PL08X_BURST_SZ_64:
			val |= PL080_BSIZE_64 <<
				FTDMAC020_CH_CSR_SRC_SIZE_SHIFT;
			break;
		case PL08X_BURST_SZ_128:
			val |= PL080_BSIZE_128 <<
				FTDMAC020_CH_CSR_SRC_SIZE_SHIFT;
			break;
		case PL08X_BURST_SZ_256:
			val |= PL080_BSIZE_256 <<
				FTDMAC020_CH_CSR_SRC_SIZE_SHIFT;
			break;
		}

		/* Protection flags */
		if (pl08x->pd->memcpy_prot_buff)
			val |= FTDMAC020_CH_CSR_PROT2;
		if (pl08x->pd->memcpy_prot_cache)
			val |= FTDMAC020_CH_CSR_PROT3;
		/* We are the kernel, so we are in privileged mode */
		val |= FTDMAC020_CH_CSR_PROT1;

		writel_relaxed(val, phychan->reg_control);
	} else {
		/* Bits are just identical */
		writel_relaxed(lli[PL080_LLI_CCTL], phychan->reg_control);
	}

	/* Second control word on the PL080s */
	if (pl08x->vd->pl080s)
		writel_relaxed(lli[PL080S_LLI_CCTL2],
				phychan->base + PL080S_CH_CONTROL2);

	writel(ccfg, phychan->reg_config);
}
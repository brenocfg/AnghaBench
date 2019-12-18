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
typedef  int uint32_t ;
struct ipu_softc {int sc_fb_phys; TYPE_1__* sc_mode; } ;
struct ipu_cpmem_ch_param {int dummy; } ;
struct TYPE_2__ {int hdisplay; scalar_t__ vdisplay; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_PARAM_RESET (struct ipu_cpmem_ch_param*) ; 
 int /*<<< orphan*/  CH_PARAM_SET_ALPHA_OFFSET (struct ipu_cpmem_ch_param*,int) ; 
 int /*<<< orphan*/  CH_PARAM_SET_ALPHA_WIDTH (struct ipu_cpmem_ch_param*,int) ; 
 int /*<<< orphan*/  CH_PARAM_SET_BLUE_OFFSET (struct ipu_cpmem_ch_param*,int) ; 
 int /*<<< orphan*/  CH_PARAM_SET_BLUE_WIDTH (struct ipu_cpmem_ch_param*,int) ; 
 int /*<<< orphan*/  CH_PARAM_SET_BPP (struct ipu_cpmem_ch_param*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CH_PARAM_SET_EBA0 (struct ipu_cpmem_ch_param*,int) ; 
 int /*<<< orphan*/  CH_PARAM_SET_EBA1 (struct ipu_cpmem_ch_param*,int) ; 
 int /*<<< orphan*/  CH_PARAM_SET_FH (struct ipu_cpmem_ch_param*,scalar_t__) ; 
 int /*<<< orphan*/  CH_PARAM_SET_FW (struct ipu_cpmem_ch_param*,int) ; 
 int /*<<< orphan*/  CH_PARAM_SET_GREEN_OFFSET (struct ipu_cpmem_ch_param*,int) ; 
 int /*<<< orphan*/  CH_PARAM_SET_GREEN_WIDTH (struct ipu_cpmem_ch_param*,int) ; 
 int /*<<< orphan*/  CH_PARAM_SET_NPB (struct ipu_cpmem_ch_param*,int) ; 
 int /*<<< orphan*/  CH_PARAM_SET_PFS (struct ipu_cpmem_ch_param*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CH_PARAM_SET_RED_OFFSET (struct ipu_cpmem_ch_param*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CH_PARAM_SET_RED_WIDTH (struct ipu_cpmem_ch_param*,int) ; 
 int /*<<< orphan*/  CH_PARAM_SET_SLY (struct ipu_cpmem_ch_param*,int) ; 
 int /*<<< orphan*/  CH_PARAM_SET_UBO (struct ipu_cpmem_ch_param*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CH_PARAM_SET_VBO (struct ipu_cpmem_ch_param*,int /*<<< orphan*/ ) ; 
 int DMA_CHANNEL ; 
 int DMFC_DP_CHAN ; 
 unsigned long DMFC_DP_CHAN_BURST_SIZE_5B (int /*<<< orphan*/ ) ; 
 unsigned long DMFC_DP_CHAN_BURST_SIZE_5F (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMFC_DP_CHAN_BURST_SIZE_8 ; 
 int DMFC_DP_CHAN_DEF ; 
 unsigned long DMFC_DP_CHAN_DEF_WM_CLR_5B (int) ; 
 unsigned long DMFC_DP_CHAN_DEF_WM_CLR_5F (int) ; 
 unsigned long DMFC_DP_CHAN_DEF_WM_CLR_6B (int) ; 
 unsigned long DMFC_DP_CHAN_DEF_WM_CLR_6F (int) ; 
 unsigned long DMFC_DP_CHAN_DEF_WM_EN_5B ; 
 unsigned long DMFC_DP_CHAN_DEF_WM_EN_5F ; 
 unsigned long DMFC_DP_CHAN_DEF_WM_SET_5B (int) ; 
 unsigned long DMFC_DP_CHAN_DEF_WM_SET_5F (int) ; 
 int /*<<< orphan*/  DMFC_DP_CHAN_FIFO_SIZE_128 ; 
 int /*<<< orphan*/  DMFC_DP_CHAN_FIFO_SIZE_256 ; 
 unsigned long DMFC_DP_CHAN_FIFO_SIZE_5B (int /*<<< orphan*/ ) ; 
 unsigned long DMFC_DP_CHAN_FIFO_SIZE_5F (int /*<<< orphan*/ ) ; 
 unsigned long DMFC_DP_CHAN_ST_ADDR_SIZE_5B (int) ; 
 unsigned long DMFC_DP_CHAN_ST_ADDR_SIZE_5F (int) ; 
 int DMFC_GENERAL_1 ; 
 int DMFC_GENERAL_1_WAIT4EOT_5B ; 
 int DMFC_IC_CTRL ; 
 unsigned long DMFC_IC_CTRL_DISABLED ; 
 int DMFC_WR_CHAN ; 
 unsigned long DMFC_WR_CHAN_BURST_SIZE_8 ; 
 int DMFC_WR_CHAN_DEF ; 
 unsigned long DMFC_WR_CHAN_DEF_WM_CLR_1 (int) ; 
 unsigned long DMFC_WR_CHAN_DEF_WM_CLR_1C (int) ; 
 unsigned long DMFC_WR_CHAN_DEF_WM_CLR_2 (int) ; 
 unsigned long DMFC_WR_CHAN_DEF_WM_CLR_2C (int) ; 
 unsigned long DMFC_WR_CHAN_DEF_WM_EN_1 ; 
 unsigned long DMFC_WR_CHAN_DEF_WM_SET_1 (int) ; 
 unsigned long DMFC_WR_CHAN_FIFO_SIZE_128 ; 
 int IPU_CH_DB_MODE_SEL_0 ; 
 int IPU_CH_DB_MODE_SEL_1 ; 
 int IPU_CUR_BUF_0 ; 
 int IPU_CUR_BUF_1 ; 
 int /*<<< orphan*/  IPU_PIX_FORMAT_BPP_16 ; 
 int /*<<< orphan*/  IPU_PIX_FORMAT_RGB ; 
 int IPU_READ4 (struct ipu_softc*,int) ; 
 int /*<<< orphan*/  IPU_WRITE4 (struct ipu_softc*,int,unsigned long) ; 
 int /*<<< orphan*/  IPU_WRITE_CH_PARAM (struct ipu_softc*,int,struct ipu_cpmem_ch_param*) ; 
 int MODE_BPP ; 
 int /*<<< orphan*/  ipu_print_channel (struct ipu_cpmem_ch_param*) ; 

__attribute__((used)) static void
ipu_init_buffer(struct ipu_softc *sc)
{
	struct ipu_cpmem_ch_param param;
	uint32_t stride;
	uint32_t reg, db_mode_sel, cur_buf;

	stride = sc->sc_mode->hdisplay * MODE_BPP / 8;

	/* init channel parameters */
	CH_PARAM_RESET(&param);
	/* XXX: interlaced modes are not supported yet */
	CH_PARAM_SET_FW(&param, sc->sc_mode->hdisplay - 1);
	CH_PARAM_SET_FH(&param, sc->sc_mode->vdisplay - 1);
	CH_PARAM_SET_SLY(&param, stride - 1);

	CH_PARAM_SET_EBA0(&param, (sc->sc_fb_phys >> 3));
	CH_PARAM_SET_EBA1(&param, (sc->sc_fb_phys >> 3));

	CH_PARAM_SET_BPP(&param, IPU_PIX_FORMAT_BPP_16);
	CH_PARAM_SET_PFS(&param, IPU_PIX_FORMAT_RGB);
	/* 16 pixels per burst access */
	CH_PARAM_SET_NPB(&param, 16 - 1);

	CH_PARAM_SET_RED_OFFSET(&param, 0);
	CH_PARAM_SET_RED_WIDTH(&param, 5 - 1);
	CH_PARAM_SET_GREEN_OFFSET(&param, 5);
	CH_PARAM_SET_GREEN_WIDTH(&param, 6 - 1);
	CH_PARAM_SET_BLUE_OFFSET(&param, 11);
	CH_PARAM_SET_BLUE_WIDTH(&param, 5 - 1);
	CH_PARAM_SET_ALPHA_OFFSET(&param, 16);
	CH_PARAM_SET_ALPHA_WIDTH(&param, 8 - 1);

	CH_PARAM_SET_UBO(&param, 0);
	CH_PARAM_SET_VBO(&param, 0);

	IPU_WRITE_CH_PARAM(sc, DMA_CHANNEL, &param);
#ifdef DEBUG
	ipu_print_channel(&param);
#endif

	/* init DMFC */
	IPU_WRITE4(sc, DMFC_IC_CTRL, DMFC_IC_CTRL_DISABLED);
	/* High resolution DP */
	IPU_WRITE4(sc, DMFC_WR_CHAN, DMFC_WR_CHAN_BURST_SIZE_8 |
	    DMFC_WR_CHAN_FIFO_SIZE_128);
	IPU_WRITE4(sc, DMFC_WR_CHAN_DEF, DMFC_WR_CHAN_DEF_WM_CLR_2C(1) |
	    DMFC_WR_CHAN_DEF_WM_CLR_1C(1) |
	    DMFC_WR_CHAN_DEF_WM_CLR_2(1) |
	    DMFC_WR_CHAN_DEF_WM_CLR_1(7) |
	    DMFC_WR_CHAN_DEF_WM_SET_1(5) |
	    DMFC_WR_CHAN_DEF_WM_EN_1);

	IPU_WRITE4(sc, DMFC_DP_CHAN,
	    DMFC_DP_CHAN_BURST_SIZE_5F(DMFC_DP_CHAN_BURST_SIZE_8) |
	    DMFC_DP_CHAN_FIFO_SIZE_5F(DMFC_DP_CHAN_FIFO_SIZE_128) |
	    DMFC_DP_CHAN_ST_ADDR_SIZE_5F(6) /* segment 6 */ |
	    DMFC_DP_CHAN_BURST_SIZE_5B(DMFC_DP_CHAN_BURST_SIZE_8) |
	    DMFC_DP_CHAN_FIFO_SIZE_5B(DMFC_DP_CHAN_FIFO_SIZE_256) |
	    DMFC_DP_CHAN_ST_ADDR_SIZE_5B(2) /* segment 2 */);

	IPU_WRITE4(sc, DMFC_DP_CHAN_DEF, DMFC_DP_CHAN_DEF_WM_CLR_6F(1) |
	    DMFC_DP_CHAN_DEF_WM_CLR_6B(1) |
	    DMFC_DP_CHAN_DEF_WM_CLR_5F(7) |
	    DMFC_DP_CHAN_DEF_WM_SET_5F(5) |
	    DMFC_DP_CHAN_DEF_WM_EN_5F |
	    DMFC_DP_CHAN_DEF_WM_CLR_5B(7) |
	    DMFC_DP_CHAN_DEF_WM_SET_5B(5) |
	    DMFC_DP_CHAN_DEF_WM_EN_5B);

	reg = IPU_READ4(sc, DMFC_GENERAL_1);
	reg &= ~(DMFC_GENERAL_1_WAIT4EOT_5B);
	IPU_WRITE4(sc, DMFC_GENERAL_1, reg);

	/* XXX: set priority? */

	/* Set single buffer mode */
	if (DMA_CHANNEL < 32) {
		db_mode_sel = IPU_CH_DB_MODE_SEL_0;
		cur_buf = IPU_CUR_BUF_0;
	} else {
		db_mode_sel = IPU_CH_DB_MODE_SEL_1;
		cur_buf = IPU_CUR_BUF_1;
	}

	reg = IPU_READ4(sc, db_mode_sel);
	reg |= (1UL << (DMA_CHANNEL & 0x1f));
	IPU_WRITE4(sc, db_mode_sel, reg);

	IPU_WRITE4(sc, cur_buf, (1UL << (DMA_CHANNEL & 0x1f)));
}
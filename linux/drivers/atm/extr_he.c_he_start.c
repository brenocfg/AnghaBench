#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct he_tpd {int dummy; } ;
struct he_hsp {int dummy; } ;
struct he_dev {int media; int vcibits; int vpibits; int cells_per_row; int bytes_per_row; int r0_numrows; int tx_numrows; int r1_numrows; int r0_startrow; int tx_startrow; int r1_startrow; int cells_per_lbuf; int buffer_limit; int r0_numbuffs; int r1_numbuffs; int tx_numbuffs; unsigned int hsp_phys; scalar_t__ tbrq_peak; scalar_t__ rbpl_peak; scalar_t__ rbrq_peak; scalar_t__ irq_peak; TYPE_4__* atm_dev; scalar_t__ total_bw; TYPE_2__* cs_stper; int /*<<< orphan*/ * hsp; struct pci_dev* pci_dev; int /*<<< orphan*/  outstanding_tpds; int /*<<< orphan*/ * tpd_pool; void** prod_id; int /*<<< orphan*/  membase; } ;
struct atm_dev {void** esi; } ;
struct TYPE_10__ {int vpi_bits; int vci_bits; } ;
struct TYPE_11__ {TYPE_3__ ci_range; TYPE_1__* phy; int /*<<< orphan*/  link_rate; } ;
struct TYPE_9__ {int pcr; scalar_t__ inuse; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* start ) (TYPE_4__*) ;} ;

/* Variables and functions */
 unsigned int ARB_RNUM_MAX (int) ; 
 unsigned int ATM_CELL_PAYLOAD ; 
 int /*<<< orphan*/  ATM_OC12_PCR ; 
 int /*<<< orphan*/  ATM_OC3_PCR ; 
 unsigned int BANK_ON ; 
 int BIG_ENDIAN_HOST ; 
 unsigned int BOARD_RST_STATUS ; 
 unsigned int BUS_MULTI (int) ; 
 scalar_t__ CEC ; 
 int CMDFF_ENB ; 
 int CONFIG_DEFAULT_VCIBITS ; 
 int CONFIG_DEFAULT_VPIBITS ; 
 unsigned int CONFIG_TMABR ; 
 unsigned int CONFIG_TPDBA ; 
 unsigned int CONFIG_TSRB ; 
 unsigned int CONFIG_TSRC ; 
 unsigned int CONFIG_TSRD ; 
 int /*<<< orphan*/  CS_ERCTL0 ; 
 int DATA_RD_SWAP ; 
 int DATA_WR_SWAP ; 
 scalar_t__ DCC ; 
 int DESC_RD_SWAP ; 
 int DESC_WR_SWAP ; 
 unsigned int DRF_THRESH (int) ; 
 int EINVAL ; 
 int ENBL_64 ; 
 int ENODEV ; 
 int ENOMEM ; 
 unsigned int ER_ENABLE ; 
 scalar_t__ G0_INMQ_L ; 
 scalar_t__ G0_INMQ_S ; 
 scalar_t__ G0_RBPL_BS ; 
 scalar_t__ G0_RBPL_QI ; 
 scalar_t__ G0_RBPL_S ; 
 scalar_t__ G0_RBPL_T ; 
 scalar_t__ G0_RBPS_BS ; 
 scalar_t__ G0_RBPS_QI ; 
 scalar_t__ G0_RBPS_S ; 
 scalar_t__ G0_RBPS_T ; 
 scalar_t__ G0_RBRQ_H ; 
 scalar_t__ G0_RBRQ_I ; 
 scalar_t__ G0_RBRQ_Q ; 
 scalar_t__ G0_RBRQ_ST ; 
 scalar_t__ G0_TBRQ_B_T ; 
 scalar_t__ G0_TBRQ_H ; 
 scalar_t__ G0_TBRQ_S ; 
 scalar_t__ G0_TBRQ_THRESH ; 
 scalar_t__ G1_INMQ_L ; 
 scalar_t__ G1_INMQ_S ; 
 scalar_t__ G2_INMQ_L ; 
 scalar_t__ G2_INMQ_S ; 
 scalar_t__ G3_INMQ_L ; 
 scalar_t__ G3_INMQ_S ; 
 scalar_t__ G4_INMQ_L ; 
 scalar_t__ G4_INMQ_S ; 
 scalar_t__ G5_INMQ_L ; 
 scalar_t__ G5_INMQ_S ; 
 scalar_t__ G6_INMQ_L ; 
 scalar_t__ G6_INMQ_S ; 
 scalar_t__ G7_INMQ_L ; 
 scalar_t__ G7_INMQ_S ; 
 int /*<<< orphan*/  GEN_CNTL_0 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct he_dev* HE_DEV (struct atm_dev*) ; 
 int HE_MAXCIDBITS ; 
 int HE_NUM_CS_STPER ; 
 int HE_NUM_GROUPS ; 
 int /*<<< orphan*/  HE_REGMAP_SIZE ; 
 scalar_t__ HOST_CNTL ; 
 int /*<<< orphan*/  HPRINTK (char*,...) ; 
 scalar_t__ HSP_BA ; 
 int IGNORE_TIMEOUT ; 
 int INIT_ENB ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int INTR_SWAP ; 
 int INT_PROC_ENBL ; 
 int LAT_TIMER ; 
 scalar_t__ LBARB ; 
 unsigned int LBFREE_CNT (int) ; 
 int LB_64_ENB ; 
 scalar_t__ LB_CONFIG ; 
 scalar_t__ LB_SWAP ; 
 scalar_t__ LITHRSH ; 
 scalar_t__ MAC_ADDR ; 
 scalar_t__ MCC ; 
 scalar_t__ MEDIA ; 
 int MRL_ENB ; 
 int MRM_ENB ; 
 unsigned int NET_PREF (int) ; 
 scalar_t__ OEC ; 
 int OUTFF_ENB ; 
 int PCI_BUS_SIZE64 ; 
 int /*<<< orphan*/  PCI_CACHE_LINE_SIZE ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int PCI_COMMAND_INVALIDATE ; 
 int PCI_COMMAND_MASTER ; 
 int PCI_COMMAND_MEMORY ; 
 int /*<<< orphan*/  PCI_LATENCY_TIMER ; 
 int PERR_INT_ENB ; 
 unsigned int PHY_INT_ENB ; 
 scalar_t__ PROD_ID ; 
 int PROD_ID_LEN ; 
 unsigned int PTMR_PRE (int) ; 
 int QUICK_RD_RETRY ; 
 int QUICK_WR_RETRY ; 
 unsigned int RBP_QSIZE (int) ; 
 unsigned int RBP_THRESH (int) ; 
 unsigned int RBRQ_SIZE (int) ; 
 unsigned int RBRQ_THRESH (int) ; 
 scalar_t__ RCMABR_BA ; 
 scalar_t__ RCMCONFIG ; 
 scalar_t__ RCMLBM_BA ; 
 scalar_t__ RCMRSRB_BA ; 
 int RCM_MEM_SIZE ; 
 scalar_t__ RC_CONFIG ; 
 unsigned int RC_UT_MODE (int) ; 
 unsigned int REF_RATE (int) ; 
 scalar_t__ RESET_CNTL ; 
 scalar_t__ RH_CONFIG ; 
 unsigned int RH_PRTY (int) ; 
 scalar_t__ RLBC_H ; 
 scalar_t__ RLBC_H2 ; 
 scalar_t__ RLBC_T ; 
 unsigned int RL_PRTY (int) ; 
 unsigned int RM_BANK_WAIT (int) ; 
 unsigned int RM_RW_WAIT (int) ; 
 scalar_t__ RXTHRSH ; 
 unsigned int RX_ENABLE ; 
 unsigned int RX_VALVC (int) ; 
 unsigned int RX_VALVP (int) ; 
 scalar_t__ SDRAMCON ; 
 scalar_t__ SDRAM_CTL ; 
 unsigned int SLICE_X (int) ; 
 int /*<<< orphan*/  SUNI_TACP_IUCHP ; 
 int SUNI_TACP_IUCHP_CLP ; 
 int /*<<< orphan*/  SUNI_TPOP_APM ; 
 int SUNI_TPOP_APM_S ; 
 int SUNI_TPOP_APM_S_SHIFT ; 
 int SUNI_TPOP_S_SDH ; 
 int SWAP_RNUM_MAX (int) ; 
 unsigned int TBRQ_THRESH (int) ; 
 scalar_t__ TCMCONFIG ; 
 int TCM_MEM_SIZE ; 
 unsigned int TH_PRTY (int) ; 
 unsigned int TL_PRTY (int) ; 
 scalar_t__ TMABR_BA ; 
 unsigned int TM_BANK_WAIT (int) ; 
 unsigned int TM_RW_WAIT (int) ; 
 int /*<<< orphan*/  TPD_ALIGNMENT ; 
 scalar_t__ TPD_BA ; 
 scalar_t__ TSRB_BA ; 
 scalar_t__ TSRC_BA ; 
 scalar_t__ TSRD_BA ; 
 scalar_t__ TXAAL5_PROTO ; 
 scalar_t__ TX_CONFIG ; 
 unsigned int TX_ENABLE ; 
 unsigned int TX_UT_MODE (int) ; 
 unsigned int TX_VCI_MASK (int) ; 
 scalar_t__ UBUFF_BA ; 
 unsigned int UT_RD_DELAY (int) ; 
 unsigned int WIDE_DATA ; 
 int XFER_SIZE ; 
 int disable64 ; 
 int /*<<< orphan*/ * dma_alloc_coherent (int /*<<< orphan*/ *,int,unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dma_pool_create (char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  he_init_cs_block (struct he_dev*) ; 
 scalar_t__ he_init_cs_block_rcm (struct he_dev*) ; 
 scalar_t__ he_init_group (struct he_dev*,int /*<<< orphan*/ ) ; 
 unsigned int he_init_irq (struct he_dev*) ; 
 int /*<<< orphan*/  he_init_rx_lbfp0 (struct he_dev*) ; 
 int /*<<< orphan*/  he_init_rx_lbfp1 (struct he_dev*) ; 
 int /*<<< orphan*/  he_init_tpdrq (struct he_dev*) ; 
 int /*<<< orphan*/  he_init_tx_lbfp (struct he_dev*) ; 
 scalar_t__ he_is622 (struct he_dev*) ; 
 scalar_t__ he_isMM (struct he_dev*) ; 
 int he_phy_get (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  he_phy_put (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 void* he_readl (struct he_dev*,scalar_t__) ; 
 unsigned int he_readl_mbox (struct he_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  he_writel (struct he_dev*,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  he_writel_mbox (struct he_dev*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  he_writel_rcm (struct he_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  he_writel_tcm (struct he_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hprintk (char*,...) ; 
 int /*<<< orphan*/  ioremap (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int nvcibits ; 
 int nvpibits ; 
 scalar_t__ pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 unsigned long pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 void* read_prom_byte (struct he_dev*,scalar_t__) ; 
 scalar_t__ sdh ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  suni_init (TYPE_4__*) ; 

__attribute__((used)) static int he_start(struct atm_dev *dev)
{
	struct he_dev *he_dev;
	struct pci_dev *pci_dev;
	unsigned long membase;

	u16 command;
	u32 gen_cntl_0, host_cntl, lb_swap;
	u8 cache_size, timer;
	
	unsigned err;
	unsigned int status, reg;
	int i, group;

	he_dev = HE_DEV(dev);
	pci_dev = he_dev->pci_dev;

	membase = pci_resource_start(pci_dev, 0);
	HPRINTK("membase = 0x%lx  irq = %d.\n", membase, pci_dev->irq);

	/*
	 * pci bus controller initialization 
	 */

	/* 4.3 pci bus controller-specific initialization */
	if (pci_read_config_dword(pci_dev, GEN_CNTL_0, &gen_cntl_0) != 0) {
		hprintk("can't read GEN_CNTL_0\n");
		return -EINVAL;
	}
	gen_cntl_0 |= (MRL_ENB | MRM_ENB | IGNORE_TIMEOUT);
	if (pci_write_config_dword(pci_dev, GEN_CNTL_0, gen_cntl_0) != 0) {
		hprintk("can't write GEN_CNTL_0.\n");
		return -EINVAL;
	}

	if (pci_read_config_word(pci_dev, PCI_COMMAND, &command) != 0) {
		hprintk("can't read PCI_COMMAND.\n");
		return -EINVAL;
	}

	command |= (PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER | PCI_COMMAND_INVALIDATE);
	if (pci_write_config_word(pci_dev, PCI_COMMAND, command) != 0) {
		hprintk("can't enable memory.\n");
		return -EINVAL;
	}

	if (pci_read_config_byte(pci_dev, PCI_CACHE_LINE_SIZE, &cache_size)) {
		hprintk("can't read cache line size?\n");
		return -EINVAL;
	}

	if (cache_size < 16) {
		cache_size = 16;
		if (pci_write_config_byte(pci_dev, PCI_CACHE_LINE_SIZE, cache_size))
			hprintk("can't set cache line size to %d\n", cache_size);
	}

	if (pci_read_config_byte(pci_dev, PCI_LATENCY_TIMER, &timer)) {
		hprintk("can't read latency timer?\n");
		return -EINVAL;
	}

	/* from table 3.9
	 *
	 * LAT_TIMER = 1 + AVG_LAT + BURST_SIZE/BUS_SIZE
	 * 
	 * AVG_LAT: The average first data read/write latency [maximum 16 clock cycles]
	 * BURST_SIZE: 1536 bytes (read) for 622, 768 bytes (read) for 155 [192 clock cycles]
	 *
	 */ 
#define LAT_TIMER 209
	if (timer < LAT_TIMER) {
		HPRINTK("latency timer was %d, setting to %d\n", timer, LAT_TIMER);
		timer = LAT_TIMER;
		if (pci_write_config_byte(pci_dev, PCI_LATENCY_TIMER, timer))
			hprintk("can't set latency timer to %d\n", timer);
	}

	if (!(he_dev->membase = ioremap(membase, HE_REGMAP_SIZE))) {
		hprintk("can't set up page mapping\n");
		return -EINVAL;
	}

	/* 4.4 card reset */
	he_writel(he_dev, 0x0, RESET_CNTL);
	he_writel(he_dev, 0xff, RESET_CNTL);

	msleep(16);	/* 16 ms */
	status = he_readl(he_dev, RESET_CNTL);
	if ((status & BOARD_RST_STATUS) == 0) {
		hprintk("reset failed\n");
		return -EINVAL;
	}

	/* 4.5 set bus width */
	host_cntl = he_readl(he_dev, HOST_CNTL);
	if (host_cntl & PCI_BUS_SIZE64)
		gen_cntl_0 |= ENBL_64;
	else
		gen_cntl_0 &= ~ENBL_64;

	if (disable64 == 1) {
		hprintk("disabling 64-bit pci bus transfers\n");
		gen_cntl_0 &= ~ENBL_64;
	}

	if (gen_cntl_0 & ENBL_64)
		hprintk("64-bit transfers enabled\n");

	pci_write_config_dword(pci_dev, GEN_CNTL_0, gen_cntl_0);

	/* 4.7 read prom contents */
	for (i = 0; i < PROD_ID_LEN; ++i)
		he_dev->prod_id[i] = read_prom_byte(he_dev, PROD_ID + i);

	he_dev->media = read_prom_byte(he_dev, MEDIA);

	for (i = 0; i < 6; ++i)
		dev->esi[i] = read_prom_byte(he_dev, MAC_ADDR + i);

	hprintk("%s%s, %pM\n", he_dev->prod_id,
		he_dev->media & 0x40 ? "SM" : "MM", dev->esi);
	he_dev->atm_dev->link_rate = he_is622(he_dev) ?
						ATM_OC12_PCR : ATM_OC3_PCR;

	/* 4.6 set host endianess */
	lb_swap = he_readl(he_dev, LB_SWAP);
	if (he_is622(he_dev))
		lb_swap &= ~XFER_SIZE;		/* 4 cells */
	else
		lb_swap |= XFER_SIZE;		/* 8 cells */
#ifdef __BIG_ENDIAN
	lb_swap |= DESC_WR_SWAP | INTR_SWAP | BIG_ENDIAN_HOST;
#else
	lb_swap &= ~(DESC_WR_SWAP | INTR_SWAP | BIG_ENDIAN_HOST |
			DATA_WR_SWAP | DATA_RD_SWAP | DESC_RD_SWAP);
#endif /* __BIG_ENDIAN */
	he_writel(he_dev, lb_swap, LB_SWAP);

	/* 4.8 sdram controller initialization */
	he_writel(he_dev, he_is622(he_dev) ? LB_64_ENB : 0x0, SDRAM_CTL);

	/* 4.9 initialize rnum value */
	lb_swap |= SWAP_RNUM_MAX(0xf);
	he_writel(he_dev, lb_swap, LB_SWAP);

	/* 4.10 initialize the interrupt queues */
	if ((err = he_init_irq(he_dev)) != 0)
		return err;

	/* 4.11 enable pci bus controller state machines */
	host_cntl |= (OUTFF_ENB | CMDFF_ENB |
				QUICK_RD_RETRY | QUICK_WR_RETRY | PERR_INT_ENB);
	he_writel(he_dev, host_cntl, HOST_CNTL);

	gen_cntl_0 |= INT_PROC_ENBL|INIT_ENB;
	pci_write_config_dword(pci_dev, GEN_CNTL_0, gen_cntl_0);

	/*
	 * atm network controller initialization
	 */

	/* 5.1.1 generic configuration state */

	/*
	 *		local (cell) buffer memory map
	 *                    
	 *             HE155                          HE622
	 *                                                      
	 *        0 ____________1023 bytes  0 _______________________2047 bytes
	 *         |            |            |                   |   |
	 *         |  utility   |            |        rx0        |   |
	 *        5|____________|         255|___________________| u |
	 *        6|            |         256|                   | t |
	 *         |            |            |                   | i |
	 *         |    rx0     |     row    |        tx         | l |
	 *         |            |            |                   | i |
	 *         |            |         767|___________________| t |
	 *      517|____________|         768|                   | y |
	 * row  518|            |            |        rx1        |   |
	 *         |            |        1023|___________________|___|
	 *         |            |
	 *         |    tx      |
	 *         |            |
	 *         |            |
	 *     1535|____________|
	 *     1536|            |
	 *         |    rx1     |
	 *     2047|____________|
	 *
	 */

	/* total 4096 connections */
	he_dev->vcibits = CONFIG_DEFAULT_VCIBITS;
	he_dev->vpibits = CONFIG_DEFAULT_VPIBITS;

	if (nvpibits != -1 && nvcibits != -1 && nvpibits+nvcibits != HE_MAXCIDBITS) {
		hprintk("nvpibits + nvcibits != %d\n", HE_MAXCIDBITS);
		return -ENODEV;
	}

	if (nvpibits != -1) {
		he_dev->vpibits = nvpibits;
		he_dev->vcibits = HE_MAXCIDBITS - nvpibits;
	}

	if (nvcibits != -1) {
		he_dev->vcibits = nvcibits;
		he_dev->vpibits = HE_MAXCIDBITS - nvcibits;
	}


	if (he_is622(he_dev)) {
		he_dev->cells_per_row = 40;
		he_dev->bytes_per_row = 2048;
		he_dev->r0_numrows = 256;
		he_dev->tx_numrows = 512;
		he_dev->r1_numrows = 256;
		he_dev->r0_startrow = 0;
		he_dev->tx_startrow = 256;
		he_dev->r1_startrow = 768;
	} else {
		he_dev->cells_per_row = 20;
		he_dev->bytes_per_row = 1024;
		he_dev->r0_numrows = 512;
		he_dev->tx_numrows = 1018;
		he_dev->r1_numrows = 512;
		he_dev->r0_startrow = 6;
		he_dev->tx_startrow = 518;
		he_dev->r1_startrow = 1536;
	}

	he_dev->cells_per_lbuf = 4;
	he_dev->buffer_limit = 4;
	he_dev->r0_numbuffs = he_dev->r0_numrows *
				he_dev->cells_per_row / he_dev->cells_per_lbuf;
	if (he_dev->r0_numbuffs > 2560)
		he_dev->r0_numbuffs = 2560;

	he_dev->r1_numbuffs = he_dev->r1_numrows *
				he_dev->cells_per_row / he_dev->cells_per_lbuf;
	if (he_dev->r1_numbuffs > 2560)
		he_dev->r1_numbuffs = 2560;

	he_dev->tx_numbuffs = he_dev->tx_numrows *
				he_dev->cells_per_row / he_dev->cells_per_lbuf;
	if (he_dev->tx_numbuffs > 5120)
		he_dev->tx_numbuffs = 5120;

	/* 5.1.2 configure hardware dependent registers */

	he_writel(he_dev, 
		SLICE_X(0x2) | ARB_RNUM_MAX(0xf) | TH_PRTY(0x3) |
		RH_PRTY(0x3) | TL_PRTY(0x2) | RL_PRTY(0x1) |
		(he_is622(he_dev) ? BUS_MULTI(0x28) : BUS_MULTI(0x46)) |
		(he_is622(he_dev) ? NET_PREF(0x50) : NET_PREF(0x8c)),
								LBARB);

	he_writel(he_dev, BANK_ON |
		(he_is622(he_dev) ? (REF_RATE(0x384) | WIDE_DATA) : REF_RATE(0x150)),
								SDRAMCON);

	he_writel(he_dev,
		(he_is622(he_dev) ? RM_BANK_WAIT(1) : RM_BANK_WAIT(0)) |
						RM_RW_WAIT(1), RCMCONFIG);
	he_writel(he_dev,
		(he_is622(he_dev) ? TM_BANK_WAIT(2) : TM_BANK_WAIT(1)) |
						TM_RW_WAIT(1), TCMCONFIG);

	he_writel(he_dev, he_dev->cells_per_lbuf * ATM_CELL_PAYLOAD, LB_CONFIG);

	he_writel(he_dev, 
		(he_is622(he_dev) ? UT_RD_DELAY(8) : UT_RD_DELAY(0)) |
		(he_is622(he_dev) ? RC_UT_MODE(0) : RC_UT_MODE(1)) |
		RX_VALVP(he_dev->vpibits) |
		RX_VALVC(he_dev->vcibits),			 RC_CONFIG);

	he_writel(he_dev, DRF_THRESH(0x20) |
		(he_is622(he_dev) ? TX_UT_MODE(0) : TX_UT_MODE(1)) |
		TX_VCI_MASK(he_dev->vcibits) |
		LBFREE_CNT(he_dev->tx_numbuffs), 		TX_CONFIG);

	he_writel(he_dev, 0x0, TXAAL5_PROTO);

	he_writel(he_dev, PHY_INT_ENB |
		(he_is622(he_dev) ? PTMR_PRE(67 - 1) : PTMR_PRE(50 - 1)),
								RH_CONFIG);

	/* 5.1.3 initialize connection memory */

	for (i = 0; i < TCM_MEM_SIZE; ++i)
		he_writel_tcm(he_dev, 0, i);

	for (i = 0; i < RCM_MEM_SIZE; ++i)
		he_writel_rcm(he_dev, 0, i);

	/*
	 *	transmit connection memory map
	 *
	 *                  tx memory
	 *          0x0 ___________________
	 *             |                   |
	 *             |                   |
	 *             |       TSRa        |
	 *             |                   |
	 *             |                   |
	 *       0x8000|___________________|
	 *             |                   |
	 *             |       TSRb        |
	 *       0xc000|___________________|
	 *             |                   |
	 *             |       TSRc        |
	 *       0xe000|___________________|
	 *             |       TSRd        |
	 *       0xf000|___________________|
	 *             |       tmABR       |
	 *      0x10000|___________________|
	 *             |                   |
	 *             |       tmTPD       |
	 *             |___________________|
	 *             |                   |
	 *                      ....
	 *      0x1ffff|___________________|
	 *
	 *
	 */

	he_writel(he_dev, CONFIG_TSRB, TSRB_BA);
	he_writel(he_dev, CONFIG_TSRC, TSRC_BA);
	he_writel(he_dev, CONFIG_TSRD, TSRD_BA);
	he_writel(he_dev, CONFIG_TMABR, TMABR_BA);
	he_writel(he_dev, CONFIG_TPDBA, TPD_BA);


	/*
	 *	receive connection memory map
	 *
	 *          0x0 ___________________
	 *             |                   |
	 *             |                   |
	 *             |       RSRa        |
	 *             |                   |
	 *             |                   |
	 *       0x8000|___________________|
	 *             |                   |
	 *             |             rx0/1 |
	 *             |       LBM         |   link lists of local
	 *             |             tx    |   buffer memory 
	 *             |                   |
	 *       0xd000|___________________|
	 *             |                   |
	 *             |      rmABR        |
	 *       0xe000|___________________|
	 *             |                   |
	 *             |       RSRb        |
	 *             |___________________|
	 *             |                   |
	 *                      ....
	 *       0xffff|___________________|
	 */

	he_writel(he_dev, 0x08000, RCMLBM_BA);
	he_writel(he_dev, 0x0e000, RCMRSRB_BA);
	he_writel(he_dev, 0x0d800, RCMABR_BA);

	/* 5.1.4 initialize local buffer free pools linked lists */

	he_init_rx_lbfp0(he_dev);
	he_init_rx_lbfp1(he_dev);

	he_writel(he_dev, 0x0, RLBC_H);
	he_writel(he_dev, 0x0, RLBC_T);
	he_writel(he_dev, 0x0, RLBC_H2);

	he_writel(he_dev, 512, RXTHRSH);	/* 10% of r0+r1 buffers */
	he_writel(he_dev, 256, LITHRSH); 	/* 5% of r0+r1 buffers */

	he_init_tx_lbfp(he_dev);

	he_writel(he_dev, he_is622(he_dev) ? 0x104780 : 0x800, UBUFF_BA);

	/* 5.1.5 initialize intermediate receive queues */

	if (he_is622(he_dev)) {
		he_writel(he_dev, 0x000f, G0_INMQ_S);
		he_writel(he_dev, 0x200f, G0_INMQ_L);

		he_writel(he_dev, 0x001f, G1_INMQ_S);
		he_writel(he_dev, 0x201f, G1_INMQ_L);

		he_writel(he_dev, 0x002f, G2_INMQ_S);
		he_writel(he_dev, 0x202f, G2_INMQ_L);

		he_writel(he_dev, 0x003f, G3_INMQ_S);
		he_writel(he_dev, 0x203f, G3_INMQ_L);

		he_writel(he_dev, 0x004f, G4_INMQ_S);
		he_writel(he_dev, 0x204f, G4_INMQ_L);

		he_writel(he_dev, 0x005f, G5_INMQ_S);
		he_writel(he_dev, 0x205f, G5_INMQ_L);

		he_writel(he_dev, 0x006f, G6_INMQ_S);
		he_writel(he_dev, 0x206f, G6_INMQ_L);

		he_writel(he_dev, 0x007f, G7_INMQ_S);
		he_writel(he_dev, 0x207f, G7_INMQ_L);
	} else {
		he_writel(he_dev, 0x0000, G0_INMQ_S);
		he_writel(he_dev, 0x0008, G0_INMQ_L);

		he_writel(he_dev, 0x0001, G1_INMQ_S);
		he_writel(he_dev, 0x0009, G1_INMQ_L);

		he_writel(he_dev, 0x0002, G2_INMQ_S);
		he_writel(he_dev, 0x000a, G2_INMQ_L);

		he_writel(he_dev, 0x0003, G3_INMQ_S);
		he_writel(he_dev, 0x000b, G3_INMQ_L);

		he_writel(he_dev, 0x0004, G4_INMQ_S);
		he_writel(he_dev, 0x000c, G4_INMQ_L);

		he_writel(he_dev, 0x0005, G5_INMQ_S);
		he_writel(he_dev, 0x000d, G5_INMQ_L);

		he_writel(he_dev, 0x0006, G6_INMQ_S);
		he_writel(he_dev, 0x000e, G6_INMQ_L);

		he_writel(he_dev, 0x0007, G7_INMQ_S);
		he_writel(he_dev, 0x000f, G7_INMQ_L);
	}

	/* 5.1.6 application tunable parameters */

	he_writel(he_dev, 0x0, MCC);
	he_writel(he_dev, 0x0, OEC);
	he_writel(he_dev, 0x0, DCC);
	he_writel(he_dev, 0x0, CEC);
	
	/* 5.1.7 cs block initialization */

	he_init_cs_block(he_dev);

	/* 5.1.8 cs block connection memory initialization */
	
	if (he_init_cs_block_rcm(he_dev) < 0)
		return -ENOMEM;

	/* 5.1.10 initialize host structures */

	he_init_tpdrq(he_dev);

	he_dev->tpd_pool = dma_pool_create("tpd", &he_dev->pci_dev->dev,
					   sizeof(struct he_tpd), TPD_ALIGNMENT, 0);
	if (he_dev->tpd_pool == NULL) {
		hprintk("unable to create tpd dma_pool\n");
		return -ENOMEM;         
	}

	INIT_LIST_HEAD(&he_dev->outstanding_tpds);

	if (he_init_group(he_dev, 0) != 0)
		return -ENOMEM;

	for (group = 1; group < HE_NUM_GROUPS; ++group) {
		he_writel(he_dev, 0x0, G0_RBPS_S + (group * 32));
		he_writel(he_dev, 0x0, G0_RBPS_T + (group * 32));
		he_writel(he_dev, 0x0, G0_RBPS_QI + (group * 32));
		he_writel(he_dev, RBP_THRESH(0x1) | RBP_QSIZE(0x0),
						G0_RBPS_BS + (group * 32));

		he_writel(he_dev, 0x0, G0_RBPL_S + (group * 32));
		he_writel(he_dev, 0x0, G0_RBPL_T + (group * 32));
		he_writel(he_dev, RBP_THRESH(0x1) | RBP_QSIZE(0x0),
						G0_RBPL_QI + (group * 32));
		he_writel(he_dev, 0x0, G0_RBPL_BS + (group * 32));

		he_writel(he_dev, 0x0, G0_RBRQ_ST + (group * 16));
		he_writel(he_dev, 0x0, G0_RBRQ_H + (group * 16));
		he_writel(he_dev, RBRQ_THRESH(0x1) | RBRQ_SIZE(0x0),
						G0_RBRQ_Q + (group * 16));
		he_writel(he_dev, 0x0, G0_RBRQ_I + (group * 16));

		he_writel(he_dev, 0x0, G0_TBRQ_B_T + (group * 16));
		he_writel(he_dev, 0x0, G0_TBRQ_H + (group * 16));
		he_writel(he_dev, TBRQ_THRESH(0x1),
						G0_TBRQ_THRESH + (group * 16));
		he_writel(he_dev, 0x0, G0_TBRQ_S + (group * 16));
	}

	/* host status page */

	he_dev->hsp = dma_alloc_coherent(&he_dev->pci_dev->dev,
					 sizeof(struct he_hsp),
					 &he_dev->hsp_phys, GFP_KERNEL);
	if (he_dev->hsp == NULL) {
		hprintk("failed to allocate host status page\n");
		return -ENOMEM;
	}
	he_writel(he_dev, he_dev->hsp_phys, HSP_BA);

	/* initialize framer */

#ifdef CONFIG_ATM_HE_USE_SUNI
	if (he_isMM(he_dev))
		suni_init(he_dev->atm_dev);
	if (he_dev->atm_dev->phy && he_dev->atm_dev->phy->start)
		he_dev->atm_dev->phy->start(he_dev->atm_dev);
#endif /* CONFIG_ATM_HE_USE_SUNI */

	if (sdh) {
		/* this really should be in suni.c but for now... */
		int val;

		val = he_phy_get(he_dev->atm_dev, SUNI_TPOP_APM);
		val = (val & ~SUNI_TPOP_APM_S) | (SUNI_TPOP_S_SDH << SUNI_TPOP_APM_S_SHIFT);
		he_phy_put(he_dev->atm_dev, val, SUNI_TPOP_APM);
		he_phy_put(he_dev->atm_dev, SUNI_TACP_IUCHP_CLP, SUNI_TACP_IUCHP);
	}

	/* 5.1.12 enable transmit and receive */

	reg = he_readl_mbox(he_dev, CS_ERCTL0);
	reg |= TX_ENABLE|ER_ENABLE;
	he_writel_mbox(he_dev, reg, CS_ERCTL0);

	reg = he_readl(he_dev, RC_CONFIG);
	reg |= RX_ENABLE;
	he_writel(he_dev, reg, RC_CONFIG);

	for (i = 0; i < HE_NUM_CS_STPER; ++i) {
		he_dev->cs_stper[i].inuse = 0;
		he_dev->cs_stper[i].pcr = -1;
	}
	he_dev->total_bw = 0;


	/* atm linux initialization */

	he_dev->atm_dev->ci_range.vpi_bits = he_dev->vpibits;
	he_dev->atm_dev->ci_range.vci_bits = he_dev->vcibits;

	he_dev->irq_peak = 0;
	he_dev->rbrq_peak = 0;
	he_dev->rbpl_peak = 0;
	he_dev->tbrq_peak = 0;

	HPRINTK("hell bent for leather!\n");

	return 0;
}
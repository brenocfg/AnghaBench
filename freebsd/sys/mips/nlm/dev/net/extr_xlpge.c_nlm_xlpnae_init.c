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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct nlm_xlpnae_softc {int nucores; int sgmiimask; int xauimask; int /*<<< orphan*/  portcfg; int /*<<< orphan*/  base; scalar_t__ ieee_1588_en; int /*<<< orphan*/  prepad_size; scalar_t__ prepad_en; scalar_t__ hw_parser_en; int /*<<< orphan*/  poedv_base; int /*<<< orphan*/  poe_base; int /*<<< orphan*/  max_ports; int /*<<< orphan*/  flow_crc_poly; int /*<<< orphan*/  ncontexts; int /*<<< orphan*/  freq; int /*<<< orphan*/  nblocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFS_DEVICE_NAE ; 
 int /*<<< orphan*/  MAX_POE_CLASSES ; 
 int /*<<< orphan*/  NAE_LANE_CFG_SOFTRESET ; 
 int /*<<< orphan*/  NAE_RX_CONFIG ; 
 int /*<<< orphan*/  NAE_TX_CONFIG ; 
 int /*<<< orphan*/  nlm_config_poe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_deflate_frin_fifo_carving (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_enable_hardware_parser (int /*<<< orphan*/ ) ; 
 scalar_t__ nlm_is_xlp8xx_ax () ; 
 int /*<<< orphan*/  nlm_mdio_reset_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_nae_flush_free_fifo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_prepad_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nlm_read_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_reset_nae (int) ; 
 int nlm_set_device_frequency (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_setup_1588_timer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_setup_flow_crc_poly (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_setup_interfaces (struct nlm_xlpnae_softc*) ; 
 int /*<<< orphan*/  nlm_setup_poe_class_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_setup_rx_cal_cfg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_setup_tx_cal_cfg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_setup_vfbid_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_sgmii_pcs_init (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nlm_ucore_load_all (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  nlm_write_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nlm_xaui_pcs_init (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  poe_cl_tbl ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
nlm_xlpnae_init(int node, struct nlm_xlpnae_softc *sc)
{
	uint64_t nae_base;
	uint32_t ucoremask = 0;
	uint32_t val;
	int i;

	nae_base = sc->base;

	nlm_nae_flush_free_fifo(nae_base, sc->nblocks);
	nlm_deflate_frin_fifo_carving(nae_base, sc->max_ports);
	nlm_reset_nae(node);

	for (i = 0; i < sc->nucores; i++)	/* XXXJC: code repeated below */
		ucoremask |= (0x1 << i);
	printf("Loading 0x%x ucores with microcode\n", ucoremask);
	nlm_ucore_load_all(nae_base, ucoremask, 1);

	val = nlm_set_device_frequency(node, DFS_DEVICE_NAE, sc->freq);
	printf("Setup NAE frequency to %dMHz\n", val);

	nlm_mdio_reset_all(nae_base);

	printf("Initialze SGMII PCS for blocks 0x%x\n", sc->sgmiimask);
	nlm_sgmii_pcs_init(nae_base, sc->sgmiimask);

	printf("Initialze XAUI PCS for blocks 0x%x\n", sc->xauimask);
	nlm_xaui_pcs_init(nae_base, sc->xauimask);

	/* clear NETIOR soft reset */
	nlm_write_nae_reg(nae_base, NAE_LANE_CFG_SOFTRESET, 0x0);

	/* Disable RX enable bit in RX_CONFIG */
	val = nlm_read_nae_reg(nae_base, NAE_RX_CONFIG);
	val &= 0xfffffffe;
	nlm_write_nae_reg(nae_base, NAE_RX_CONFIG, val);

	if (nlm_is_xlp8xx_ax() == 0) {
		val = nlm_read_nae_reg(nae_base, NAE_TX_CONFIG);
		val &= ~(1 << 3);
		nlm_write_nae_reg(nae_base, NAE_TX_CONFIG, val);
	}

	nlm_setup_poe_class_config(nae_base, MAX_POE_CLASSES,
	    sc->ncontexts, poe_cl_tbl);

	nlm_setup_vfbid_mapping(nae_base);

	nlm_setup_flow_crc_poly(nae_base, sc->flow_crc_poly);

	nlm_setup_rx_cal_cfg(nae_base, sc->max_ports, sc->portcfg);
	/* note: xlp8xx Ax does not have Tx Calendering */
	if (!nlm_is_xlp8xx_ax())
		nlm_setup_tx_cal_cfg(nae_base, sc->max_ports, sc->portcfg);

	nlm_setup_interfaces(sc);
	nlm_config_poe(sc->poe_base, sc->poedv_base);

	if (sc->hw_parser_en)
		nlm_enable_hardware_parser(nae_base);

	if (sc->prepad_en)
		nlm_prepad_enable(nae_base, sc->prepad_size);

	if (sc->ieee_1588_en)
		nlm_setup_1588_timer(sc->base, sc->portcfg);
}
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
typedef  int uint64_t ;
typedef  int u_int ;
struct fire_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_pcib_mtx; int /*<<< orphan*/  sc_stats_ilu_err; int /*<<< orphan*/  sc_stats_tlu_oe_non_fatal; int /*<<< orphan*/  sc_stats_tlu_oe_tx_err; int /*<<< orphan*/  sc_stats_tlu_oe_rx_err; int /*<<< orphan*/  sc_stats_tlu_ce; int /*<<< orphan*/  sc_stats_mmu_err; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int FIRE_PCI_ILU_ERR_INT_IHB_PE_P ; 
 int FIRE_PCI_MMU_ERR_INT_TTC_DPE_P ; 
 int FIRE_PCI_READ_8 (struct fire_softc*,int /*<<< orphan*/ ) ; 
 int FIRE_PCI_TLU_OEVENT_EHP_P ; 
 int FIRE_PCI_TLU_OEVENT_EIP_P ; 
 int FIRE_PCI_TLU_OEVENT_ERP_P ; 
 int FIRE_PCI_TLU_UERR_INT_PP_P ; 
 int /*<<< orphan*/  FIRE_PCI_WRITE_8 (struct fire_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FO_PCI_DMC_CORE_BLOCK_ERR_STAT ; 
 int FO_PCI_DMC_CORE_BLOCK_INT_EN_IMU ; 
 int FO_PCI_DMC_CORE_BLOCK_INT_EN_MMU ; 
 int /*<<< orphan*/  FO_PCI_ILU_INT_STAT ; 
 int /*<<< orphan*/  FO_PCI_IMU_EQS_ERR_LOG ; 
 int FO_PCI_IMU_ERR_INT_COR_MES_NOT_EN_P ; 
 int FO_PCI_IMU_ERR_INT_EQ_NOT_EN_P ; 
 int FO_PCI_IMU_ERR_INT_EQ_OVER_P ; 
 int FO_PCI_IMU_ERR_INT_FATAL_MES_NOT_EN_P ; 
 int FO_PCI_IMU_ERR_INT_MSI_MAL_ERR_P ; 
 int FO_PCI_IMU_ERR_INT_MSI_NOT_EN_P ; 
 int FO_PCI_IMU_ERR_INT_MSI_PAR_ERR_P ; 
 int FO_PCI_IMU_ERR_INT_NFATAL_MES_NOT_EN_P ; 
 int FO_PCI_IMU_ERR_INT_PMEACK_MES_NOT_EN_P ; 
 int FO_PCI_IMU_ERR_INT_PMPME_MES_NOT_EN_P ; 
 int /*<<< orphan*/  FO_PCI_IMU_INT_STAT ; 
 int /*<<< orphan*/  FO_PCI_IMU_RDS_ERR_LOG ; 
 int /*<<< orphan*/  FO_PCI_IMU_SCS_ERR_LOG ; 
 int /*<<< orphan*/  FO_PCI_LPU_LNK_LYR_INT_STAT ; 
 int /*<<< orphan*/  FO_PCI_LPU_PHY_LYR_INT_STAT ; 
 int FO_PCI_MMU_ERR_INT_TBW_DME_P ; 
 int FO_PCI_MMU_ERR_INT_TBW_DPE_P ; 
 int FO_PCI_MMU_ERR_INT_TBW_ERR_P ; 
 int FO_PCI_MMU_ERR_INT_TBW_UDE_P ; 
 int FO_PCI_MMU_ERR_INT_TRN_ERR_P ; 
 int FO_PCI_MMU_ERR_INT_TTC_CAE_P ; 
 int /*<<< orphan*/  FO_PCI_MMU_ERR_STAT_CLR ; 
 int /*<<< orphan*/  FO_PCI_MMU_INT_STAT ; 
 int /*<<< orphan*/  FO_PCI_MMU_TRANS_FAULT_ADDR ; 
 int /*<<< orphan*/  FO_PCI_MMU_TRANS_FAULT_STAT ; 
 int /*<<< orphan*/  FO_PCI_MULTI_CORE_ERR_STAT ; 
 int FO_PCI_MULTI_CORE_ERR_STAT_DMC ; 
 int FO_PCI_MULTI_CORE_ERR_STAT_PEC ; 
 int /*<<< orphan*/  FO_PCI_PEC_CORE_BLOCK_INT_STAT ; 
 int FO_PCI_PEC_CORE_BLOCK_INT_STAT_CERR ; 
 int FO_PCI_PEC_CORE_BLOCK_INT_STAT_ILU ; 
 int FO_PCI_PEC_CORE_BLOCK_INT_STAT_OEVENT ; 
 int FO_PCI_PEC_CORE_BLOCK_INT_STAT_UERR ; 
 int FO_PCI_TLU_CERR_INT_RE_P ; 
 int /*<<< orphan*/  FO_PCI_TLU_CERR_INT_STAT ; 
 int /*<<< orphan*/  FO_PCI_TLU_CERR_STAT_CLR ; 
 int FO_PCI_TLU_OEVENT_CRS_P ; 
 int FO_PCI_TLU_OEVENT_CTO_P ; 
 int FO_PCI_TLU_OEVENT_EDP_P ; 
 int FO_PCI_TLU_OEVENT_EMP_P ; 
 int FO_PCI_TLU_OEVENT_EPE_P ; 
 int FO_PCI_TLU_OEVENT_ERO_P ; 
 int FO_PCI_TLU_OEVENT_ERU_P ; 
 int FO_PCI_TLU_OEVENT_IIP_P ; 
 int /*<<< orphan*/  FO_PCI_TLU_OEVENT_INT_STAT ; 
 int FO_PCI_TLU_OEVENT_LDN_P ; 
 int FO_PCI_TLU_OEVENT_LIN_P ; 
 int FO_PCI_TLU_OEVENT_LRS_P ; 
 int FO_PCI_TLU_OEVENT_LUP_P ; 
 int FO_PCI_TLU_OEVENT_LWC_P ; 
 int FO_PCI_TLU_OEVENT_MFC_P ; 
 int FO_PCI_TLU_OEVENT_MRC_P ; 
 int FO_PCI_TLU_OEVENT_NFP_P ; 
 int FO_PCI_TLU_OEVENT_RUC_P ; 
 int /*<<< orphan*/  FO_PCI_TLU_OEVENT_STAT_CLR ; 
 int FO_PCI_TLU_OEVENT_WUC_P ; 
 int /*<<< orphan*/  FO_PCI_TLU_RX_OEVENT_HDR1_LOG ; 
 int /*<<< orphan*/  FO_PCI_TLU_RX_OEVENT_HDR2_LOG ; 
 int /*<<< orphan*/  FO_PCI_TLU_RX_UERR_HDR1_LOG ; 
 int /*<<< orphan*/  FO_PCI_TLU_RX_UERR_HDR2_LOG ; 
 int /*<<< orphan*/  FO_PCI_TLU_TX_OEVENT_HDR1_LOG ; 
 int /*<<< orphan*/  FO_PCI_TLU_TX_OEVENT_HDR2_LOG ; 
 int /*<<< orphan*/  FO_PCI_TLU_TX_UERR_HDR1_LOG ; 
 int /*<<< orphan*/  FO_PCI_TLU_TX_UERR_HDR2_LOG ; 
 int FO_PCI_TLU_UERR_INT_CTO_P ; 
 int FO_PCI_TLU_UERR_INT_DLP_P ; 
 int FO_PCI_TLU_UERR_INT_MFP_P ; 
 int FO_PCI_TLU_UERR_INT_ROF_P ; 
 int /*<<< orphan*/  FO_PCI_TLU_UERR_INT_STAT ; 
 int FO_PCI_TLU_UERR_INT_TE_P ; 
 int FO_PCI_TLU_UERR_INT_UC_P ; 
 int FO_PCI_TLU_UERR_INT_UR_P ; 
 int OBERON_PCI_MMU_ERR_INT_TTC_DUE_P ; 
 int OBERON_PCI_TLU_OEVENT_EIUE_P ; 
 int OBERON_PCI_TLU_OEVENT_ERBU_P ; 
 int OBERON_PCI_TLU_OEVENT_TLUEITMO_S ; 
 int OBERON_PCI_TLU_UERR_INT_POIS_P ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,unsigned long long,...) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fire_dmc_pec(void *arg)
{
	struct fire_softc *sc;
	device_t dev;
	uint64_t cestat, dmcstat, ilustat, imustat, mcstat, mmustat, mmutfar;
	uint64_t mmutfsr, oestat, pecstat, uestat, val;
	u_int fatal, oenfatal;

	fatal = 0;
	sc = arg;
	dev = sc->sc_dev;
	mtx_lock_spin(&sc->sc_pcib_mtx);
	mcstat = FIRE_PCI_READ_8(sc, FO_PCI_MULTI_CORE_ERR_STAT);
	if ((mcstat & FO_PCI_MULTI_CORE_ERR_STAT_DMC) != 0) {
		dmcstat = FIRE_PCI_READ_8(sc, FO_PCI_DMC_CORE_BLOCK_ERR_STAT);
		if ((dmcstat & FO_PCI_DMC_CORE_BLOCK_INT_EN_IMU) != 0) {
			imustat = FIRE_PCI_READ_8(sc, FO_PCI_IMU_INT_STAT);
			device_printf(dev, "IMU error %#llx\n",
			    (unsigned long long)imustat);
			if ((imustat &
			    FO_PCI_IMU_ERR_INT_EQ_NOT_EN_P) != 0) {
				fatal = 1;
				val = FIRE_PCI_READ_8(sc,
				    FO_PCI_IMU_SCS_ERR_LOG);
				device_printf(dev, "SCS error log %#llx\n",
				    (unsigned long long)val);
			}
			if ((imustat & FO_PCI_IMU_ERR_INT_EQ_OVER_P) != 0) {
				fatal = 1;
				val = FIRE_PCI_READ_8(sc,
				    FO_PCI_IMU_EQS_ERR_LOG);
				device_printf(dev, "EQS error log %#llx\n",
				    (unsigned long long)val);
			}
			if ((imustat & (FO_PCI_IMU_ERR_INT_MSI_MAL_ERR_P |
			    FO_PCI_IMU_ERR_INT_MSI_PAR_ERR_P |
			    FO_PCI_IMU_ERR_INT_PMEACK_MES_NOT_EN_P |
			    FO_PCI_IMU_ERR_INT_PMPME_MES_NOT_EN_P |
			    FO_PCI_IMU_ERR_INT_FATAL_MES_NOT_EN_P |
			    FO_PCI_IMU_ERR_INT_NFATAL_MES_NOT_EN_P |
			    FO_PCI_IMU_ERR_INT_COR_MES_NOT_EN_P |
			    FO_PCI_IMU_ERR_INT_MSI_NOT_EN_P)) != 0) {
				fatal = 1;
				val = FIRE_PCI_READ_8(sc,
				    FO_PCI_IMU_RDS_ERR_LOG);
				device_printf(dev, "RDS error log %#llx\n",
				    (unsigned long long)val);
			}
		}
		if ((dmcstat & FO_PCI_DMC_CORE_BLOCK_INT_EN_MMU) != 0) {
			fatal = 1;
			mmustat = FIRE_PCI_READ_8(sc, FO_PCI_MMU_INT_STAT);
			mmutfar = FIRE_PCI_READ_8(sc,
			    FO_PCI_MMU_TRANS_FAULT_ADDR);
			mmutfsr = FIRE_PCI_READ_8(sc,
			    FO_PCI_MMU_TRANS_FAULT_STAT);
			if ((mmustat & (FO_PCI_MMU_ERR_INT_TBW_DPE_P |
			    FO_PCI_MMU_ERR_INT_TBW_ERR_P |
			    FO_PCI_MMU_ERR_INT_TBW_UDE_P |
			    FO_PCI_MMU_ERR_INT_TBW_DME_P |
			    FO_PCI_MMU_ERR_INT_TTC_CAE_P |
			    FIRE_PCI_MMU_ERR_INT_TTC_DPE_P |
			    OBERON_PCI_MMU_ERR_INT_TTC_DUE_P |
			    FO_PCI_MMU_ERR_INT_TRN_ERR_P)) != 0)
				fatal = 1;
			else {
				sc->sc_stats_mmu_err++;
				FIRE_PCI_WRITE_8(sc, FO_PCI_MMU_ERR_STAT_CLR,
				    mmustat);
			}
			device_printf(dev,
			    "MMU error %#llx: TFAR %#llx TFSR %#llx\n",
			    (unsigned long long)mmustat,
			    (unsigned long long)mmutfar,
			    (unsigned long long)mmutfsr);
		}
	}
	if ((mcstat & FO_PCI_MULTI_CORE_ERR_STAT_PEC) != 0) {
		pecstat = FIRE_PCI_READ_8(sc, FO_PCI_PEC_CORE_BLOCK_INT_STAT);
		if ((pecstat & FO_PCI_PEC_CORE_BLOCK_INT_STAT_UERR) != 0) {
			fatal = 1;
			uestat = FIRE_PCI_READ_8(sc,
			    FO_PCI_TLU_UERR_INT_STAT);
			device_printf(dev,
			    "DLU/TLU uncorrectable error %#llx\n",
			    (unsigned long long)uestat);
			if ((uestat & (FO_PCI_TLU_UERR_INT_UR_P |
			    OBERON_PCI_TLU_UERR_INT_POIS_P |
			    FO_PCI_TLU_UERR_INT_MFP_P |
			    FO_PCI_TLU_UERR_INT_ROF_P |
			    FO_PCI_TLU_UERR_INT_UC_P |
			    FIRE_PCI_TLU_UERR_INT_PP_P |
			    OBERON_PCI_TLU_UERR_INT_POIS_P)) != 0) {
				val = FIRE_PCI_READ_8(sc,
				    FO_PCI_TLU_RX_UERR_HDR1_LOG);
				device_printf(dev,
				    "receive header log %#llx\n",
				    (unsigned long long)val);
				val = FIRE_PCI_READ_8(sc,
				    FO_PCI_TLU_RX_UERR_HDR2_LOG);
				device_printf(dev,
				    "receive header log 2 %#llx\n",
				    (unsigned long long)val);
			}
			if ((uestat & FO_PCI_TLU_UERR_INT_CTO_P) != 0) {
				val = FIRE_PCI_READ_8(sc,
				    FO_PCI_TLU_TX_UERR_HDR1_LOG);
				device_printf(dev,
				    "transmit header log %#llx\n",
				    (unsigned long long)val);
				val = FIRE_PCI_READ_8(sc,
				    FO_PCI_TLU_TX_UERR_HDR2_LOG);
				device_printf(dev,
				    "transmit header log 2 %#llx\n",
				    (unsigned long long)val);
			}
			if ((uestat & FO_PCI_TLU_UERR_INT_DLP_P) != 0) {
				val = FIRE_PCI_READ_8(sc,
				    FO_PCI_LPU_LNK_LYR_INT_STAT);
				device_printf(dev,
				    "link layer interrupt and status %#llx\n",
				    (unsigned long long)val);
			}
			if ((uestat & FO_PCI_TLU_UERR_INT_TE_P) != 0) {
				val = FIRE_PCI_READ_8(sc,
				    FO_PCI_LPU_PHY_LYR_INT_STAT);
				device_printf(dev,
				    "phy layer interrupt and status %#llx\n",
				    (unsigned long long)val);
			}
		}
		if ((pecstat & FO_PCI_PEC_CORE_BLOCK_INT_STAT_CERR) != 0) {
			sc->sc_stats_tlu_ce++;
			cestat = FIRE_PCI_READ_8(sc,
			    FO_PCI_TLU_CERR_INT_STAT);
			device_printf(dev,
			    "DLU/TLU correctable error %#llx\n",
			    (unsigned long long)cestat);
			val = FIRE_PCI_READ_8(sc,
			    FO_PCI_LPU_LNK_LYR_INT_STAT);
			device_printf(dev,
			    "link layer interrupt and status %#llx\n",
			    (unsigned long long)val);
			if ((cestat & FO_PCI_TLU_CERR_INT_RE_P) != 0) {
				FIRE_PCI_WRITE_8(sc,
				    FO_PCI_LPU_LNK_LYR_INT_STAT, val);
				val = FIRE_PCI_READ_8(sc,
				    FO_PCI_LPU_PHY_LYR_INT_STAT);
				device_printf(dev,
				    "phy layer interrupt and status %#llx\n",
				    (unsigned long long)val);
			}
			FIRE_PCI_WRITE_8(sc, FO_PCI_TLU_CERR_STAT_CLR,
			    cestat);
		}
		if ((pecstat & FO_PCI_PEC_CORE_BLOCK_INT_STAT_OEVENT) != 0) {
			oenfatal = 0;
			oestat = FIRE_PCI_READ_8(sc,
			    FO_PCI_TLU_OEVENT_INT_STAT);
			device_printf(dev, "DLU/TLU other event %#llx\n",
			    (unsigned long long)oestat);
			if ((oestat & (FO_PCI_TLU_OEVENT_MFC_P |
			    FO_PCI_TLU_OEVENT_MRC_P |
			    FO_PCI_TLU_OEVENT_WUC_P |
			    FO_PCI_TLU_OEVENT_RUC_P |
			    FO_PCI_TLU_OEVENT_CRS_P)) != 0) {
				val = FIRE_PCI_READ_8(sc,
				    FO_PCI_TLU_RX_OEVENT_HDR1_LOG);
				device_printf(dev,
				    "receive header log %#llx\n",
				    (unsigned long long)val);
				val = FIRE_PCI_READ_8(sc,
				    FO_PCI_TLU_RX_OEVENT_HDR2_LOG);
				device_printf(dev,
				    "receive header log 2 %#llx\n",
				    (unsigned long long)val);
				if ((oestat & (FO_PCI_TLU_OEVENT_MFC_P |
				    FO_PCI_TLU_OEVENT_MRC_P |
				    FO_PCI_TLU_OEVENT_WUC_P |
				    FO_PCI_TLU_OEVENT_RUC_P)) != 0)
					fatal = 1;
				else {
					sc->sc_stats_tlu_oe_rx_err++;
					oenfatal = 1;
				}
			}
			if ((oestat & (FO_PCI_TLU_OEVENT_MFC_P |
			    FO_PCI_TLU_OEVENT_CTO_P |
			    FO_PCI_TLU_OEVENT_WUC_P |
			    FO_PCI_TLU_OEVENT_RUC_P)) != 0) {
				val = FIRE_PCI_READ_8(sc,
				    FO_PCI_TLU_TX_OEVENT_HDR1_LOG);
				device_printf(dev,
				    "transmit header log %#llx\n",
				    (unsigned long long)val);
				val = FIRE_PCI_READ_8(sc,
				    FO_PCI_TLU_TX_OEVENT_HDR2_LOG);
				device_printf(dev,
				    "transmit header log 2 %#llx\n",
				    (unsigned long long)val);
				if ((oestat & (FO_PCI_TLU_OEVENT_MFC_P |
				    FO_PCI_TLU_OEVENT_CTO_P |
				    FO_PCI_TLU_OEVENT_WUC_P |
				    FO_PCI_TLU_OEVENT_RUC_P)) != 0)
					fatal = 1;
				else {
					sc->sc_stats_tlu_oe_tx_err++;
					oenfatal = 1;
				}
			}
			if ((oestat & (FO_PCI_TLU_OEVENT_ERO_P |
			    FO_PCI_TLU_OEVENT_EMP_P |
			    FO_PCI_TLU_OEVENT_EPE_P |
			    FIRE_PCI_TLU_OEVENT_ERP_P |
			    OBERON_PCI_TLU_OEVENT_ERBU_P |
			    FIRE_PCI_TLU_OEVENT_EIP_P |
			    OBERON_PCI_TLU_OEVENT_EIUE_P)) != 0) {
				fatal = 1;
				val = FIRE_PCI_READ_8(sc,
				    FO_PCI_LPU_LNK_LYR_INT_STAT);
				device_printf(dev,
				    "link layer interrupt and status %#llx\n",
				    (unsigned long long)val);
			}
			if ((oestat & (FO_PCI_TLU_OEVENT_IIP_P |
			    FO_PCI_TLU_OEVENT_EDP_P |
			    FIRE_PCI_TLU_OEVENT_EHP_P |
			    OBERON_PCI_TLU_OEVENT_TLUEITMO_S |
			    FO_PCI_TLU_OEVENT_ERU_P)) != 0)
				fatal = 1;
			if ((oestat & (FO_PCI_TLU_OEVENT_NFP_P |
			    FO_PCI_TLU_OEVENT_LWC_P |
			    FO_PCI_TLU_OEVENT_LIN_P |
			    FO_PCI_TLU_OEVENT_LRS_P |
			    FO_PCI_TLU_OEVENT_LDN_P |
			    FO_PCI_TLU_OEVENT_LUP_P)) != 0)
				oenfatal = 1;
			if (oenfatal != 0) {
				sc->sc_stats_tlu_oe_non_fatal++;
				FIRE_PCI_WRITE_8(sc,
				    FO_PCI_TLU_OEVENT_STAT_CLR, oestat);
				if ((oestat & FO_PCI_TLU_OEVENT_LIN_P) != 0)
					FIRE_PCI_WRITE_8(sc,
					    FO_PCI_LPU_LNK_LYR_INT_STAT,
					    FIRE_PCI_READ_8(sc,
					    FO_PCI_LPU_LNK_LYR_INT_STAT));
			}
		}
		if ((pecstat & FO_PCI_PEC_CORE_BLOCK_INT_STAT_ILU) != 0) {
			ilustat = FIRE_PCI_READ_8(sc, FO_PCI_ILU_INT_STAT);
			device_printf(dev, "ILU error %#llx\n",
			    (unsigned long long)ilustat);
			if ((ilustat & (FIRE_PCI_ILU_ERR_INT_IHB_PE_P |
			    FIRE_PCI_ILU_ERR_INT_IHB_PE_P)) != 0)
			    fatal = 1;
			else {
				sc->sc_stats_ilu_err++;
				FIRE_PCI_WRITE_8(sc, FO_PCI_ILU_INT_STAT,
				    ilustat);
			}
		}
	}
	mtx_unlock_spin(&sc->sc_pcib_mtx);
	if (fatal != 0)
		panic("%s: fatal DMC/PEC error",
		    device_get_nameunit(sc->sc_dev));
	return (FILTER_HANDLED);
}
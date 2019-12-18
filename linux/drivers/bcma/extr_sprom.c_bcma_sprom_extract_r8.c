#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct TYPE_9__ {void* a3; void* a2; void* a1; void* a0; } ;
struct TYPE_10__ {TYPE_3__ antenna_gain; scalar_t__ il0mac; scalar_t__ const* core_pwr_info; } ;
struct bcma_bus {TYPE_4__ sprom; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_12__ {int /*<<< orphan*/ * pa_5gh; int /*<<< orphan*/ * pa_5g; int /*<<< orphan*/ * pa_5gl; int /*<<< orphan*/  maxpwr_5gl; int /*<<< orphan*/  maxpwr_5gh; int /*<<< orphan*/  maxpwr_5g; int /*<<< orphan*/  itssi_5g; int /*<<< orphan*/ * pa_2g; int /*<<< orphan*/  maxpwr_2g; int /*<<< orphan*/  itssi_2g; } ;
struct TYPE_8__ {int /*<<< orphan*/  antswlut; int /*<<< orphan*/  tr_iso; int /*<<< orphan*/  pdet_range; int /*<<< orphan*/  extpa_gain; int /*<<< orphan*/  tssipos; } ;
struct TYPE_7__ {int /*<<< orphan*/  antswlut; int /*<<< orphan*/  tr_iso; int /*<<< orphan*/  pdet_range; int /*<<< orphan*/  extpa_gain; int /*<<< orphan*/  tssipos; } ;
struct TYPE_11__ {TYPE_2__ ghz5; TYPE_1__ ghz2; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__ const*) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  SPEX (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  SPEX32 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPEX_ARRAY8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SPOFF (int /*<<< orphan*/ ) ; 
 scalar_t__ SSB_SPROM1_SPID ; 
 int SSB_SPROM4_TXPID2G0 ; 
 scalar_t__ SSB_SPROM4_TXPID2G01 ; 
 int SSB_SPROM4_TXPID2G0_SHIFT ; 
 int SSB_SPROM4_TXPID2G1 ; 
 int SSB_SPROM4_TXPID2G1_SHIFT ; 
 int SSB_SPROM4_TXPID2G2 ; 
 scalar_t__ SSB_SPROM4_TXPID2G23 ; 
 int SSB_SPROM4_TXPID2G2_SHIFT ; 
 int SSB_SPROM4_TXPID2G3 ; 
 int SSB_SPROM4_TXPID2G3_SHIFT ; 
 int SSB_SPROM4_TXPID5G0 ; 
 scalar_t__ SSB_SPROM4_TXPID5G01 ; 
 int SSB_SPROM4_TXPID5G0_SHIFT ; 
 int SSB_SPROM4_TXPID5G1 ; 
 int SSB_SPROM4_TXPID5G1_SHIFT ; 
 int SSB_SPROM4_TXPID5G2 ; 
 scalar_t__ SSB_SPROM4_TXPID5G23 ; 
 int SSB_SPROM4_TXPID5G2_SHIFT ; 
 int SSB_SPROM4_TXPID5G3 ; 
 int SSB_SPROM4_TXPID5G3_SHIFT ; 
 int SSB_SPROM4_TXPID5GH0 ; 
 scalar_t__ SSB_SPROM4_TXPID5GH01 ; 
 int SSB_SPROM4_TXPID5GH0_SHIFT ; 
 int SSB_SPROM4_TXPID5GH1 ; 
 int SSB_SPROM4_TXPID5GH1_SHIFT ; 
 int SSB_SPROM4_TXPID5GH2 ; 
 scalar_t__ SSB_SPROM4_TXPID5GH23 ; 
 int SSB_SPROM4_TXPID5GH2_SHIFT ; 
 int SSB_SPROM4_TXPID5GH3 ; 
 int SSB_SPROM4_TXPID5GH3_SHIFT ; 
 int SSB_SPROM4_TXPID5GL0 ; 
 scalar_t__ SSB_SPROM4_TXPID5GL01 ; 
 int SSB_SPROM4_TXPID5GL0_SHIFT ; 
 int SSB_SPROM4_TXPID5GL1 ; 
 int SSB_SPROM4_TXPID5GL1_SHIFT ; 
 int SSB_SPROM4_TXPID5GL2 ; 
 scalar_t__ SSB_SPROM4_TXPID5GL23 ; 
 int SSB_SPROM4_TXPID5GL2_SHIFT ; 
 int SSB_SPROM4_TXPID5GL3 ; 
 int SSB_SPROM4_TXPID5GL3_SHIFT ; 
 int SSB_SPROM8_2G_ITSSI ; 
 int SSB_SPROM8_2G_ITSSI_SHIFT ; 
 int SSB_SPROM8_2G_MAXP ; 
 int /*<<< orphan*/  SSB_SPROM8_2G_MCSPO ; 
 scalar_t__ SSB_SPROM8_5GHL_MAXP ; 
 int SSB_SPROM8_5GH_MAXP ; 
 int /*<<< orphan*/  SSB_SPROM8_5GH_MCSPO ; 
 int SSB_SPROM8_5GL_MAXP ; 
 int SSB_SPROM8_5GL_MAXP_SHIFT ; 
 int /*<<< orphan*/  SSB_SPROM8_5GL_MCSPO ; 
 int SSB_SPROM8_5G_ITSSI ; 
 int SSB_SPROM8_5G_ITSSI_SHIFT ; 
 int SSB_SPROM8_5G_MAXP ; 
 int /*<<< orphan*/  SSB_SPROM8_5G_MCSPO ; 
 int /*<<< orphan*/  SSB_SPROM8_AGAIN0 ; 
 int /*<<< orphan*/  SSB_SPROM8_AGAIN01 ; 
 int /*<<< orphan*/  SSB_SPROM8_AGAIN0_SHIFT ; 
 int /*<<< orphan*/  SSB_SPROM8_AGAIN1 ; 
 int /*<<< orphan*/  SSB_SPROM8_AGAIN1_SHIFT ; 
 int /*<<< orphan*/  SSB_SPROM8_AGAIN2 ; 
 int /*<<< orphan*/  SSB_SPROM8_AGAIN23 ; 
 int /*<<< orphan*/  SSB_SPROM8_AGAIN2_SHIFT ; 
 int /*<<< orphan*/  SSB_SPROM8_AGAIN3 ; 
 int /*<<< orphan*/  SSB_SPROM8_AGAIN3_SHIFT ; 
 scalar_t__ SSB_SPROM8_ANTAVAIL ; 
 int SSB_SPROM8_ANTAVAIL_A ; 
 int SSB_SPROM8_ANTAVAIL_A_SHIFT ; 
 int SSB_SPROM8_ANTAVAIL_BG ; 
 int SSB_SPROM8_ANTAVAIL_BG_SHIFT ; 
 scalar_t__ SSB_SPROM8_BFL2HI ; 
 scalar_t__ SSB_SPROM8_BFL2LO ; 
 scalar_t__ SSB_SPROM8_BFLHI ; 
 scalar_t__ SSB_SPROM8_BFLLO ; 
 scalar_t__ SSB_SPROM8_BOARDREV ; 
 scalar_t__ SSB_SPROM8_BW40PO ; 
 scalar_t__ SSB_SPROM8_BWDUPPO ; 
 int SSB_SPROM8_BXA2G ; 
 int SSB_SPROM8_BXA2G_SHIFT ; 
 int SSB_SPROM8_BXA5G ; 
 int SSB_SPROM8_BXA5G_SHIFT ; 
 scalar_t__ SSB_SPROM8_CCK2GPO ; 
 scalar_t__ SSB_SPROM8_CCODE ; 
 scalar_t__ SSB_SPROM8_CDDPO ; 
 scalar_t__ SSB_SPROM8_FEM2G ; 
 scalar_t__ SSB_SPROM8_FEM5G ; 
 scalar_t__ SSB_SPROM8_GPIOA ; 
 int SSB_SPROM8_GPIOA_P0 ; 
 int SSB_SPROM8_GPIOA_P1 ; 
 int SSB_SPROM8_GPIOA_P1_SHIFT ; 
 scalar_t__ SSB_SPROM8_GPIOB ; 
 int SSB_SPROM8_GPIOB_P2 ; 
 int SSB_SPROM8_GPIOB_P3 ; 
 int SSB_SPROM8_GPIOB_P3_SHIFT ; 
 scalar_t__ SSB_SPROM8_HWIQ_IQSWP ; 
 int SSB_SPROM8_HWIQ_IQSWP_FREQ_CORR ; 
 int SSB_SPROM8_HWIQ_IQSWP_FREQ_CORR_SHIFT ; 
 int SSB_SPROM8_HWIQ_IQSWP_HW_IQCAL ; 
 int SSB_SPROM8_HWIQ_IQSWP_HW_IQCAL_SHIFT ; 
 int SSB_SPROM8_HWIQ_IQSWP_IQCAL_SWP ; 
 int SSB_SPROM8_HWIQ_IQSWP_IQCAL_SWP_SHIFT ; 
 int /*<<< orphan*/  SSB_SPROM8_IL0MAC ; 
 int SSB_SPROM8_ITSSI_A ; 
 int SSB_SPROM8_ITSSI_A_SHIFT ; 
 int SSB_SPROM8_ITSSI_BG ; 
 int SSB_SPROM8_ITSSI_BG_SHIFT ; 
 scalar_t__ SSB_SPROM8_LEDDC ; 
 int SSB_SPROM8_LEDDC_OFF ; 
 int SSB_SPROM8_LEDDC_OFF_SHIFT ; 
 int SSB_SPROM8_LEDDC_ON ; 
 int SSB_SPROM8_LEDDC_ON_SHIFT ; 
 scalar_t__ SSB_SPROM8_MAXP_A ; 
 scalar_t__ SSB_SPROM8_MAXP_AHL ; 
 int SSB_SPROM8_MAXP_AH_MASK ; 
 int SSB_SPROM8_MAXP_AL_MASK ; 
 int SSB_SPROM8_MAXP_AL_SHIFT ; 
 int SSB_SPROM8_MAXP_A_MASK ; 
 scalar_t__ SSB_SPROM8_MAXP_BG ; 
 int SSB_SPROM8_MAXP_BG_MASK ; 
 scalar_t__ SSB_SPROM8_OFDM2GPO ; 
 scalar_t__ SSB_SPROM8_OFDM5GHPO ; 
 scalar_t__ SSB_SPROM8_OFDM5GLPO ; 
 scalar_t__ SSB_SPROM8_OFDM5GPO ; 
 scalar_t__ SSB_SPROM8_OPT_CORRX ; 
 int SSB_SPROM8_OPT_CORRX_TEMPCORRX ; 
 int SSB_SPROM8_OPT_CORRX_TEMPCORRX_SHIFT ; 
 int SSB_SPROM8_OPT_CORRX_TEMP_OPTION ; 
 int SSB_SPROM8_OPT_CORRX_TEMP_OPTION_SHIFT ; 
 int SSB_SPROM8_OPT_CORRX_TEMP_SLOPE ; 
 int SSB_SPROM8_OPT_CORRX_TEMP_SLOPE_SHIFT ; 
 scalar_t__ SSB_SPROM8_PA0B0 ; 
 scalar_t__ SSB_SPROM8_PA0B1 ; 
 scalar_t__ SSB_SPROM8_PA0B2 ; 
 scalar_t__ SSB_SPROM8_PA1B0 ; 
 scalar_t__ SSB_SPROM8_PA1B1 ; 
 scalar_t__ SSB_SPROM8_PA1B2 ; 
 scalar_t__ SSB_SPROM8_PA1HIB0 ; 
 scalar_t__ SSB_SPROM8_PA1HIB1 ; 
 scalar_t__ SSB_SPROM8_PA1HIB2 ; 
 scalar_t__ SSB_SPROM8_PA1LOB0 ; 
 scalar_t__ SSB_SPROM8_PA1LOB1 ; 
 scalar_t__ SSB_SPROM8_PA1LOB2 ; 
 scalar_t__ SSB_SPROM8_RAWTS ; 
 int SSB_SPROM8_RAWTS_MEASPOWER ; 
 int SSB_SPROM8_RAWTS_MEASPOWER_SHIFT ; 
 int SSB_SPROM8_RAWTS_RAWTEMP ; 
 int SSB_SPROM8_RAWTS_RAWTEMP_SHIFT ; 
 scalar_t__ SSB_SPROM8_RSSIPARM2G ; 
 scalar_t__ SSB_SPROM8_RSSIPARM5G ; 
 int SSB_SPROM8_RSSISAV2G ; 
 int SSB_SPROM8_RSSISAV2G_SHIFT ; 
 int SSB_SPROM8_RSSISAV5G ; 
 int SSB_SPROM8_RSSISAV5G_SHIFT ; 
 int SSB_SPROM8_RSSISMC2G ; 
 int SSB_SPROM8_RSSISMC2G_SHIFT ; 
 int SSB_SPROM8_RSSISMC5G ; 
 int SSB_SPROM8_RSSISMC5G_SHIFT ; 
 int SSB_SPROM8_RSSISMF2G ; 
 int SSB_SPROM8_RSSISMF5G ; 
 scalar_t__ SSB_SPROM8_RXPO ; 
 int SSB_SPROM8_RXPO2G ; 
 int SSB_SPROM8_RXPO2G_SHIFT ; 
 int SSB_SPROM8_RXPO5G ; 
 int SSB_SPROM8_RXPO5G_SHIFT ; 
 scalar_t__ SSB_SPROM8_STBCPO ; 
 scalar_t__ SSB_SPROM8_TEMPDELTA ; 
 int SSB_SPROM8_TEMPDELTA_HYSTERESIS ; 
 int SSB_SPROM8_TEMPDELTA_HYSTERESIS_SHIFT ; 
 int SSB_SPROM8_TEMPDELTA_PERIOD ; 
 int SSB_SPROM8_TEMPDELTA_PERIOD_SHIFT ; 
 int SSB_SPROM8_TEMPDELTA_PHYCAL ; 
 int SSB_SPROM8_TEMPDELTA_PHYCAL_SHIFT ; 
 scalar_t__ SSB_SPROM8_THERMAL ; 
 int SSB_SPROM8_THERMAL_OFFSET ; 
 int SSB_SPROM8_THERMAL_OFFSET_SHIFT ; 
 int SSB_SPROM8_THERMAL_TRESH ; 
 int SSB_SPROM8_THERMAL_TRESH_SHIFT ; 
 scalar_t__ SSB_SPROM8_TRI25G ; 
 int SSB_SPROM8_TRI2G ; 
 int SSB_SPROM8_TRI5G ; 
 int SSB_SPROM8_TRI5GH ; 
 scalar_t__ SSB_SPROM8_TRI5GHL ; 
 int SSB_SPROM8_TRI5GH_SHIFT ; 
 int SSB_SPROM8_TRI5GL ; 
 int SSB_SPROM8_TRI5G_SHIFT ; 
 scalar_t__ SSB_SPROM8_TXRXC ; 
 int SSB_SPROM8_TXRXC_RXCHAIN ; 
 int SSB_SPROM8_TXRXC_RXCHAIN_SHIFT ; 
 int SSB_SPROM8_TXRXC_SWITCH ; 
 int SSB_SPROM8_TXRXC_SWITCH_SHIFT ; 
 int SSB_SPROM8_TXRXC_TXCHAIN ; 
 int SSB_SPROM8_TXRXC_TXCHAIN_SHIFT ; 
 scalar_t__ SSB_SROM8_2G_MAXP_ITSSI ; 
 scalar_t__ SSB_SROM8_2G_PA_0 ; 
 scalar_t__ SSB_SROM8_2G_PA_1 ; 
 scalar_t__ SSB_SROM8_2G_PA_2 ; 
 scalar_t__ SSB_SROM8_5GH_PA_0 ; 
 scalar_t__ SSB_SROM8_5GH_PA_1 ; 
 scalar_t__ SSB_SROM8_5GH_PA_2 ; 
 scalar_t__ SSB_SROM8_5GL_PA_0 ; 
 scalar_t__ SSB_SROM8_5GL_PA_1 ; 
 scalar_t__ SSB_SROM8_5GL_PA_2 ; 
 scalar_t__ SSB_SROM8_5G_MAXP_ITSSI ; 
 scalar_t__ SSB_SROM8_5G_PA_0 ; 
 scalar_t__ SSB_SROM8_5G_PA_1 ; 
 scalar_t__ SSB_SROM8_5G_PA_2 ; 
 int SSB_SROM8_FEM_ANTSWLUT ; 
 int SSB_SROM8_FEM_ANTSWLUT_SHIFT ; 
 int SSB_SROM8_FEM_EXTPA_GAIN ; 
 int SSB_SROM8_FEM_EXTPA_GAIN_SHIFT ; 
 int SSB_SROM8_FEM_PDET_RANGE ; 
 int SSB_SROM8_FEM_PDET_RANGE_SHIFT ; 
 int SSB_SROM8_FEM_TR_ISO ; 
 int SSB_SROM8_FEM_TR_ISO_SHIFT ; 
 int SSB_SROM8_FEM_TSSIPOS ; 
 int SSB_SROM8_FEM_TSSIPOS_SHIFT ; 
#define  SSB_SROM8_PWR_INFO_CORE0 131 
#define  SSB_SROM8_PWR_INFO_CORE1 130 
#define  SSB_SROM8_PWR_INFO_CORE2 129 
#define  SSB_SROM8_PWR_INFO_CORE3 128 
 int /*<<< orphan*/ * alpha2 ; 
 int /*<<< orphan*/  ant_available_a ; 
 int /*<<< orphan*/  ant_available_bg ; 
 int /*<<< orphan*/  antswitch ; 
 int /*<<< orphan*/  board_rev ; 
 int /*<<< orphan*/  board_type ; 
 int /*<<< orphan*/  boardflags2_hi ; 
 int /*<<< orphan*/  boardflags2_lo ; 
 int /*<<< orphan*/  boardflags_hi ; 
 int /*<<< orphan*/  boardflags_lo ; 
 int /*<<< orphan*/  bw40po ; 
 int /*<<< orphan*/  bwduppo ; 
 int /*<<< orphan*/  bxa2g ; 
 int /*<<< orphan*/  bxa5g ; 
 int /*<<< orphan*/  cck2gpo ; 
 int /*<<< orphan*/  cddpo ; 
 TYPE_6__* core_pwr_info ; 
 int /*<<< orphan*/  cpu_to_be16 (scalar_t__) ; 
 TYPE_5__ fem ; 
 int /*<<< orphan*/  freqoffset_corr ; 
 int /*<<< orphan*/  gpio0 ; 
 int /*<<< orphan*/  gpio1 ; 
 int /*<<< orphan*/  gpio2 ; 
 int /*<<< orphan*/  gpio3 ; 
 int /*<<< orphan*/  hw_iqcal_en ; 
 int /*<<< orphan*/  iqcal_swp_dis ; 
 int /*<<< orphan*/  itssi_a ; 
 int /*<<< orphan*/  itssi_bg ; 
 int /*<<< orphan*/  leddc_off_time ; 
 int /*<<< orphan*/  leddc_on_time ; 
 int /*<<< orphan*/  maxpwr_a ; 
 int /*<<< orphan*/  maxpwr_ah ; 
 int /*<<< orphan*/  maxpwr_al ; 
 int /*<<< orphan*/  maxpwr_bg ; 
 int /*<<< orphan*/  mcs2gpo ; 
 int /*<<< orphan*/  mcs5ghpo ; 
 int /*<<< orphan*/  mcs5glpo ; 
 int /*<<< orphan*/  mcs5gpo ; 
 int /*<<< orphan*/  measpower ; 
 int /*<<< orphan*/  ofdm2gpo ; 
 int /*<<< orphan*/  ofdm5ghpo ; 
 int /*<<< orphan*/  ofdm5glpo ; 
 int /*<<< orphan*/  ofdm5gpo ; 
 int /*<<< orphan*/  opo ; 
 int /*<<< orphan*/  pa0b0 ; 
 int /*<<< orphan*/  pa0b1 ; 
 int /*<<< orphan*/  pa0b2 ; 
 int /*<<< orphan*/  pa1b0 ; 
 int /*<<< orphan*/  pa1b1 ; 
 int /*<<< orphan*/  pa1b2 ; 
 int /*<<< orphan*/  pa1hib0 ; 
 int /*<<< orphan*/  pa1hib1 ; 
 int /*<<< orphan*/  pa1hib2 ; 
 int /*<<< orphan*/  pa1lob0 ; 
 int /*<<< orphan*/  pa1lob1 ; 
 int /*<<< orphan*/  pa1lob2 ; 
 int /*<<< orphan*/  phycal_tempdelta ; 
 int /*<<< orphan*/  rawtempsense ; 
 int /*<<< orphan*/  rssisav2g ; 
 int /*<<< orphan*/  rssisav5g ; 
 int /*<<< orphan*/  rssismc2g ; 
 int /*<<< orphan*/  rssismc5g ; 
 int /*<<< orphan*/  rssismf2g ; 
 int /*<<< orphan*/  rssismf5g ; 
 int /*<<< orphan*/  rxchain ; 
 int /*<<< orphan*/  rxpo2g ; 
 int /*<<< orphan*/  rxpo5g ; 
 void* sprom_extract_antgain (scalar_t__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stbcpo ; 
 int /*<<< orphan*/  tempcorrx ; 
 int /*<<< orphan*/  tempoffset ; 
 int /*<<< orphan*/  temps_hysteresis ; 
 int /*<<< orphan*/  temps_period ; 
 int /*<<< orphan*/  tempsense_option ; 
 int /*<<< orphan*/  tempsense_slope ; 
 int /*<<< orphan*/  tempthresh ; 
 int /*<<< orphan*/  tri2g ; 
 int /*<<< orphan*/  tri5g ; 
 int /*<<< orphan*/  tri5gh ; 
 int /*<<< orphan*/  tri5gl ; 
 int /*<<< orphan*/  txchain ; 
 int /*<<< orphan*/ * txpid2g ; 
 int /*<<< orphan*/ * txpid5g ; 
 int /*<<< orphan*/ * txpid5gh ; 
 int /*<<< orphan*/ * txpid5gl ; 

__attribute__((used)) static void bcma_sprom_extract_r8(struct bcma_bus *bus, const u16 *sprom)
{
	u16 v, o;
	int i;
	static const u16 pwr_info_offset[] = {
		SSB_SROM8_PWR_INFO_CORE0, SSB_SROM8_PWR_INFO_CORE1,
		SSB_SROM8_PWR_INFO_CORE2, SSB_SROM8_PWR_INFO_CORE3
	};
	BUILD_BUG_ON(ARRAY_SIZE(pwr_info_offset) !=
			ARRAY_SIZE(bus->sprom.core_pwr_info));

	for (i = 0; i < 3; i++) {
		v = sprom[SPOFF(SSB_SPROM8_IL0MAC) + i];
		*(((__be16 *)bus->sprom.il0mac) + i) = cpu_to_be16(v);
	}

	SPEX(board_rev, SSB_SPROM8_BOARDREV, ~0, 0);
	SPEX(board_type, SSB_SPROM1_SPID, ~0, 0);

	SPEX(txpid2g[0], SSB_SPROM4_TXPID2G01, SSB_SPROM4_TXPID2G0,
	     SSB_SPROM4_TXPID2G0_SHIFT);
	SPEX(txpid2g[1], SSB_SPROM4_TXPID2G01, SSB_SPROM4_TXPID2G1,
	     SSB_SPROM4_TXPID2G1_SHIFT);
	SPEX(txpid2g[2], SSB_SPROM4_TXPID2G23, SSB_SPROM4_TXPID2G2,
	     SSB_SPROM4_TXPID2G2_SHIFT);
	SPEX(txpid2g[3], SSB_SPROM4_TXPID2G23, SSB_SPROM4_TXPID2G3,
	     SSB_SPROM4_TXPID2G3_SHIFT);

	SPEX(txpid5gl[0], SSB_SPROM4_TXPID5GL01, SSB_SPROM4_TXPID5GL0,
	     SSB_SPROM4_TXPID5GL0_SHIFT);
	SPEX(txpid5gl[1], SSB_SPROM4_TXPID5GL01, SSB_SPROM4_TXPID5GL1,
	     SSB_SPROM4_TXPID5GL1_SHIFT);
	SPEX(txpid5gl[2], SSB_SPROM4_TXPID5GL23, SSB_SPROM4_TXPID5GL2,
	     SSB_SPROM4_TXPID5GL2_SHIFT);
	SPEX(txpid5gl[3], SSB_SPROM4_TXPID5GL23, SSB_SPROM4_TXPID5GL3,
	     SSB_SPROM4_TXPID5GL3_SHIFT);

	SPEX(txpid5g[0], SSB_SPROM4_TXPID5G01, SSB_SPROM4_TXPID5G0,
	     SSB_SPROM4_TXPID5G0_SHIFT);
	SPEX(txpid5g[1], SSB_SPROM4_TXPID5G01, SSB_SPROM4_TXPID5G1,
	     SSB_SPROM4_TXPID5G1_SHIFT);
	SPEX(txpid5g[2], SSB_SPROM4_TXPID5G23, SSB_SPROM4_TXPID5G2,
	     SSB_SPROM4_TXPID5G2_SHIFT);
	SPEX(txpid5g[3], SSB_SPROM4_TXPID5G23, SSB_SPROM4_TXPID5G3,
	     SSB_SPROM4_TXPID5G3_SHIFT);

	SPEX(txpid5gh[0], SSB_SPROM4_TXPID5GH01, SSB_SPROM4_TXPID5GH0,
	     SSB_SPROM4_TXPID5GH0_SHIFT);
	SPEX(txpid5gh[1], SSB_SPROM4_TXPID5GH01, SSB_SPROM4_TXPID5GH1,
	     SSB_SPROM4_TXPID5GH1_SHIFT);
	SPEX(txpid5gh[2], SSB_SPROM4_TXPID5GH23, SSB_SPROM4_TXPID5GH2,
	     SSB_SPROM4_TXPID5GH2_SHIFT);
	SPEX(txpid5gh[3], SSB_SPROM4_TXPID5GH23, SSB_SPROM4_TXPID5GH3,
	     SSB_SPROM4_TXPID5GH3_SHIFT);

	SPEX(boardflags_lo, SSB_SPROM8_BFLLO, ~0, 0);
	SPEX(boardflags_hi, SSB_SPROM8_BFLHI, ~0, 0);
	SPEX(boardflags2_lo, SSB_SPROM8_BFL2LO, ~0, 0);
	SPEX(boardflags2_hi, SSB_SPROM8_BFL2HI, ~0, 0);

	SPEX(alpha2[0], SSB_SPROM8_CCODE, 0xff00, 8);
	SPEX(alpha2[1], SSB_SPROM8_CCODE, 0x00ff, 0);

	/* Extract cores power info info */
	for (i = 0; i < ARRAY_SIZE(pwr_info_offset); i++) {
		o = pwr_info_offset[i];
		SPEX(core_pwr_info[i].itssi_2g, o + SSB_SROM8_2G_MAXP_ITSSI,
			SSB_SPROM8_2G_ITSSI, SSB_SPROM8_2G_ITSSI_SHIFT);
		SPEX(core_pwr_info[i].maxpwr_2g, o + SSB_SROM8_2G_MAXP_ITSSI,
			SSB_SPROM8_2G_MAXP, 0);

		SPEX(core_pwr_info[i].pa_2g[0], o + SSB_SROM8_2G_PA_0, ~0, 0);
		SPEX(core_pwr_info[i].pa_2g[1], o + SSB_SROM8_2G_PA_1, ~0, 0);
		SPEX(core_pwr_info[i].pa_2g[2], o + SSB_SROM8_2G_PA_2, ~0, 0);

		SPEX(core_pwr_info[i].itssi_5g, o + SSB_SROM8_5G_MAXP_ITSSI,
			SSB_SPROM8_5G_ITSSI, SSB_SPROM8_5G_ITSSI_SHIFT);
		SPEX(core_pwr_info[i].maxpwr_5g, o + SSB_SROM8_5G_MAXP_ITSSI,
			SSB_SPROM8_5G_MAXP, 0);
		SPEX(core_pwr_info[i].maxpwr_5gh, o + SSB_SPROM8_5GHL_MAXP,
			SSB_SPROM8_5GH_MAXP, 0);
		SPEX(core_pwr_info[i].maxpwr_5gl, o + SSB_SPROM8_5GHL_MAXP,
			SSB_SPROM8_5GL_MAXP, SSB_SPROM8_5GL_MAXP_SHIFT);

		SPEX(core_pwr_info[i].pa_5gl[0], o + SSB_SROM8_5GL_PA_0, ~0, 0);
		SPEX(core_pwr_info[i].pa_5gl[1], o + SSB_SROM8_5GL_PA_1, ~0, 0);
		SPEX(core_pwr_info[i].pa_5gl[2], o + SSB_SROM8_5GL_PA_2, ~0, 0);
		SPEX(core_pwr_info[i].pa_5g[0], o + SSB_SROM8_5G_PA_0, ~0, 0);
		SPEX(core_pwr_info[i].pa_5g[1], o + SSB_SROM8_5G_PA_1, ~0, 0);
		SPEX(core_pwr_info[i].pa_5g[2], o + SSB_SROM8_5G_PA_2, ~0, 0);
		SPEX(core_pwr_info[i].pa_5gh[0], o + SSB_SROM8_5GH_PA_0, ~0, 0);
		SPEX(core_pwr_info[i].pa_5gh[1], o + SSB_SROM8_5GH_PA_1, ~0, 0);
		SPEX(core_pwr_info[i].pa_5gh[2], o + SSB_SROM8_5GH_PA_2, ~0, 0);
	}

	SPEX(fem.ghz2.tssipos, SSB_SPROM8_FEM2G, SSB_SROM8_FEM_TSSIPOS,
	     SSB_SROM8_FEM_TSSIPOS_SHIFT);
	SPEX(fem.ghz2.extpa_gain, SSB_SPROM8_FEM2G, SSB_SROM8_FEM_EXTPA_GAIN,
	     SSB_SROM8_FEM_EXTPA_GAIN_SHIFT);
	SPEX(fem.ghz2.pdet_range, SSB_SPROM8_FEM2G, SSB_SROM8_FEM_PDET_RANGE,
	     SSB_SROM8_FEM_PDET_RANGE_SHIFT);
	SPEX(fem.ghz2.tr_iso, SSB_SPROM8_FEM2G, SSB_SROM8_FEM_TR_ISO,
	     SSB_SROM8_FEM_TR_ISO_SHIFT);
	SPEX(fem.ghz2.antswlut, SSB_SPROM8_FEM2G, SSB_SROM8_FEM_ANTSWLUT,
	     SSB_SROM8_FEM_ANTSWLUT_SHIFT);

	SPEX(fem.ghz5.tssipos, SSB_SPROM8_FEM5G, SSB_SROM8_FEM_TSSIPOS,
	     SSB_SROM8_FEM_TSSIPOS_SHIFT);
	SPEX(fem.ghz5.extpa_gain, SSB_SPROM8_FEM5G, SSB_SROM8_FEM_EXTPA_GAIN,
	     SSB_SROM8_FEM_EXTPA_GAIN_SHIFT);
	SPEX(fem.ghz5.pdet_range, SSB_SPROM8_FEM5G, SSB_SROM8_FEM_PDET_RANGE,
	     SSB_SROM8_FEM_PDET_RANGE_SHIFT);
	SPEX(fem.ghz5.tr_iso, SSB_SPROM8_FEM5G, SSB_SROM8_FEM_TR_ISO,
	     SSB_SROM8_FEM_TR_ISO_SHIFT);
	SPEX(fem.ghz5.antswlut, SSB_SPROM8_FEM5G, SSB_SROM8_FEM_ANTSWLUT,
	     SSB_SROM8_FEM_ANTSWLUT_SHIFT);

	SPEX(ant_available_a, SSB_SPROM8_ANTAVAIL, SSB_SPROM8_ANTAVAIL_A,
	     SSB_SPROM8_ANTAVAIL_A_SHIFT);
	SPEX(ant_available_bg, SSB_SPROM8_ANTAVAIL, SSB_SPROM8_ANTAVAIL_BG,
	     SSB_SPROM8_ANTAVAIL_BG_SHIFT);
	SPEX(maxpwr_bg, SSB_SPROM8_MAXP_BG, SSB_SPROM8_MAXP_BG_MASK, 0);
	SPEX(itssi_bg, SSB_SPROM8_MAXP_BG, SSB_SPROM8_ITSSI_BG,
	     SSB_SPROM8_ITSSI_BG_SHIFT);
	SPEX(maxpwr_a, SSB_SPROM8_MAXP_A, SSB_SPROM8_MAXP_A_MASK, 0);
	SPEX(itssi_a, SSB_SPROM8_MAXP_A, SSB_SPROM8_ITSSI_A,
	     SSB_SPROM8_ITSSI_A_SHIFT);
	SPEX(maxpwr_ah, SSB_SPROM8_MAXP_AHL, SSB_SPROM8_MAXP_AH_MASK, 0);
	SPEX(maxpwr_al, SSB_SPROM8_MAXP_AHL, SSB_SPROM8_MAXP_AL_MASK,
	     SSB_SPROM8_MAXP_AL_SHIFT);
	SPEX(gpio0, SSB_SPROM8_GPIOA, SSB_SPROM8_GPIOA_P0, 0);
	SPEX(gpio1, SSB_SPROM8_GPIOA, SSB_SPROM8_GPIOA_P1,
	     SSB_SPROM8_GPIOA_P1_SHIFT);
	SPEX(gpio2, SSB_SPROM8_GPIOB, SSB_SPROM8_GPIOB_P2, 0);
	SPEX(gpio3, SSB_SPROM8_GPIOB, SSB_SPROM8_GPIOB_P3,
	     SSB_SPROM8_GPIOB_P3_SHIFT);
	SPEX(tri2g, SSB_SPROM8_TRI25G, SSB_SPROM8_TRI2G, 0);
	SPEX(tri5g, SSB_SPROM8_TRI25G, SSB_SPROM8_TRI5G,
	     SSB_SPROM8_TRI5G_SHIFT);
	SPEX(tri5gl, SSB_SPROM8_TRI5GHL, SSB_SPROM8_TRI5GL, 0);
	SPEX(tri5gh, SSB_SPROM8_TRI5GHL, SSB_SPROM8_TRI5GH,
	     SSB_SPROM8_TRI5GH_SHIFT);
	SPEX(rxpo2g, SSB_SPROM8_RXPO, SSB_SPROM8_RXPO2G,
	     SSB_SPROM8_RXPO2G_SHIFT);
	SPEX(rxpo5g, SSB_SPROM8_RXPO, SSB_SPROM8_RXPO5G,
	     SSB_SPROM8_RXPO5G_SHIFT);
	SPEX(rssismf2g, SSB_SPROM8_RSSIPARM2G, SSB_SPROM8_RSSISMF2G, 0);
	SPEX(rssismc2g, SSB_SPROM8_RSSIPARM2G, SSB_SPROM8_RSSISMC2G,
	     SSB_SPROM8_RSSISMC2G_SHIFT);
	SPEX(rssisav2g, SSB_SPROM8_RSSIPARM2G, SSB_SPROM8_RSSISAV2G,
	     SSB_SPROM8_RSSISAV2G_SHIFT);
	SPEX(bxa2g, SSB_SPROM8_RSSIPARM2G, SSB_SPROM8_BXA2G,
	     SSB_SPROM8_BXA2G_SHIFT);
	SPEX(rssismf5g, SSB_SPROM8_RSSIPARM5G, SSB_SPROM8_RSSISMF5G, 0);
	SPEX(rssismc5g, SSB_SPROM8_RSSIPARM5G, SSB_SPROM8_RSSISMC5G,
	     SSB_SPROM8_RSSISMC5G_SHIFT);
	SPEX(rssisav5g, SSB_SPROM8_RSSIPARM5G, SSB_SPROM8_RSSISAV5G,
	     SSB_SPROM8_RSSISAV5G_SHIFT);
	SPEX(bxa5g, SSB_SPROM8_RSSIPARM5G, SSB_SPROM8_BXA5G,
	     SSB_SPROM8_BXA5G_SHIFT);

	SPEX(pa0b0, SSB_SPROM8_PA0B0, ~0, 0);
	SPEX(pa0b1, SSB_SPROM8_PA0B1, ~0, 0);
	SPEX(pa0b2, SSB_SPROM8_PA0B2, ~0, 0);
	SPEX(pa1b0, SSB_SPROM8_PA1B0, ~0, 0);
	SPEX(pa1b1, SSB_SPROM8_PA1B1, ~0, 0);
	SPEX(pa1b2, SSB_SPROM8_PA1B2, ~0, 0);
	SPEX(pa1lob0, SSB_SPROM8_PA1LOB0, ~0, 0);
	SPEX(pa1lob1, SSB_SPROM8_PA1LOB1, ~0, 0);
	SPEX(pa1lob2, SSB_SPROM8_PA1LOB2, ~0, 0);
	SPEX(pa1hib0, SSB_SPROM8_PA1HIB0, ~0, 0);
	SPEX(pa1hib1, SSB_SPROM8_PA1HIB1, ~0, 0);
	SPEX(pa1hib2, SSB_SPROM8_PA1HIB2, ~0, 0);
	SPEX(cck2gpo, SSB_SPROM8_CCK2GPO, ~0, 0);
	SPEX32(ofdm2gpo, SSB_SPROM8_OFDM2GPO, ~0, 0);
	SPEX32(ofdm5glpo, SSB_SPROM8_OFDM5GLPO, ~0, 0);
	SPEX32(ofdm5gpo, SSB_SPROM8_OFDM5GPO, ~0, 0);
	SPEX32(ofdm5ghpo, SSB_SPROM8_OFDM5GHPO, ~0, 0);

	/* Extract the antenna gain values. */
	bus->sprom.antenna_gain.a0 = sprom_extract_antgain(sprom,
							   SSB_SPROM8_AGAIN01,
							   SSB_SPROM8_AGAIN0,
							   SSB_SPROM8_AGAIN0_SHIFT);
	bus->sprom.antenna_gain.a1 = sprom_extract_antgain(sprom,
							   SSB_SPROM8_AGAIN01,
							   SSB_SPROM8_AGAIN1,
							   SSB_SPROM8_AGAIN1_SHIFT);
	bus->sprom.antenna_gain.a2 = sprom_extract_antgain(sprom,
							   SSB_SPROM8_AGAIN23,
							   SSB_SPROM8_AGAIN2,
							   SSB_SPROM8_AGAIN2_SHIFT);
	bus->sprom.antenna_gain.a3 = sprom_extract_antgain(sprom,
							   SSB_SPROM8_AGAIN23,
							   SSB_SPROM8_AGAIN3,
							   SSB_SPROM8_AGAIN3_SHIFT);

	SPEX(leddc_on_time, SSB_SPROM8_LEDDC, SSB_SPROM8_LEDDC_ON,
	     SSB_SPROM8_LEDDC_ON_SHIFT);
	SPEX(leddc_off_time, SSB_SPROM8_LEDDC, SSB_SPROM8_LEDDC_OFF,
	     SSB_SPROM8_LEDDC_OFF_SHIFT);

	SPEX(txchain, SSB_SPROM8_TXRXC, SSB_SPROM8_TXRXC_TXCHAIN,
	     SSB_SPROM8_TXRXC_TXCHAIN_SHIFT);
	SPEX(rxchain, SSB_SPROM8_TXRXC, SSB_SPROM8_TXRXC_RXCHAIN,
	     SSB_SPROM8_TXRXC_RXCHAIN_SHIFT);
	SPEX(antswitch, SSB_SPROM8_TXRXC, SSB_SPROM8_TXRXC_SWITCH,
	     SSB_SPROM8_TXRXC_SWITCH_SHIFT);

	SPEX(opo, SSB_SPROM8_OFDM2GPO, 0x00ff, 0);

	SPEX_ARRAY8(mcs2gpo, SSB_SPROM8_2G_MCSPO, ~0, 0);
	SPEX_ARRAY8(mcs5gpo, SSB_SPROM8_5G_MCSPO, ~0, 0);
	SPEX_ARRAY8(mcs5glpo, SSB_SPROM8_5GL_MCSPO, ~0, 0);
	SPEX_ARRAY8(mcs5ghpo, SSB_SPROM8_5GH_MCSPO, ~0, 0);

	SPEX(rawtempsense, SSB_SPROM8_RAWTS, SSB_SPROM8_RAWTS_RAWTEMP,
	     SSB_SPROM8_RAWTS_RAWTEMP_SHIFT);
	SPEX(measpower, SSB_SPROM8_RAWTS, SSB_SPROM8_RAWTS_MEASPOWER,
	     SSB_SPROM8_RAWTS_MEASPOWER_SHIFT);
	SPEX(tempsense_slope, SSB_SPROM8_OPT_CORRX,
	     SSB_SPROM8_OPT_CORRX_TEMP_SLOPE,
	     SSB_SPROM8_OPT_CORRX_TEMP_SLOPE_SHIFT);
	SPEX(tempcorrx, SSB_SPROM8_OPT_CORRX, SSB_SPROM8_OPT_CORRX_TEMPCORRX,
	     SSB_SPROM8_OPT_CORRX_TEMPCORRX_SHIFT);
	SPEX(tempsense_option, SSB_SPROM8_OPT_CORRX,
	     SSB_SPROM8_OPT_CORRX_TEMP_OPTION,
	     SSB_SPROM8_OPT_CORRX_TEMP_OPTION_SHIFT);
	SPEX(freqoffset_corr, SSB_SPROM8_HWIQ_IQSWP,
	     SSB_SPROM8_HWIQ_IQSWP_FREQ_CORR,
	     SSB_SPROM8_HWIQ_IQSWP_FREQ_CORR_SHIFT);
	SPEX(iqcal_swp_dis, SSB_SPROM8_HWIQ_IQSWP,
	     SSB_SPROM8_HWIQ_IQSWP_IQCAL_SWP,
	     SSB_SPROM8_HWIQ_IQSWP_IQCAL_SWP_SHIFT);
	SPEX(hw_iqcal_en, SSB_SPROM8_HWIQ_IQSWP, SSB_SPROM8_HWIQ_IQSWP_HW_IQCAL,
	     SSB_SPROM8_HWIQ_IQSWP_HW_IQCAL_SHIFT);

	SPEX(bw40po, SSB_SPROM8_BW40PO, ~0, 0);
	SPEX(cddpo, SSB_SPROM8_CDDPO, ~0, 0);
	SPEX(stbcpo, SSB_SPROM8_STBCPO, ~0, 0);
	SPEX(bwduppo, SSB_SPROM8_BWDUPPO, ~0, 0);

	SPEX(tempthresh, SSB_SPROM8_THERMAL, SSB_SPROM8_THERMAL_TRESH,
	     SSB_SPROM8_THERMAL_TRESH_SHIFT);
	SPEX(tempoffset, SSB_SPROM8_THERMAL, SSB_SPROM8_THERMAL_OFFSET,
	     SSB_SPROM8_THERMAL_OFFSET_SHIFT);
	SPEX(phycal_tempdelta, SSB_SPROM8_TEMPDELTA,
	     SSB_SPROM8_TEMPDELTA_PHYCAL,
	     SSB_SPROM8_TEMPDELTA_PHYCAL_SHIFT);
	SPEX(temps_period, SSB_SPROM8_TEMPDELTA, SSB_SPROM8_TEMPDELTA_PERIOD,
	     SSB_SPROM8_TEMPDELTA_PERIOD_SHIFT);
	SPEX(temps_hysteresis, SSB_SPROM8_TEMPDELTA,
	     SSB_SPROM8_TEMPDELTA_HYSTERESIS,
	     SSB_SPROM8_TEMPDELTA_HYSTERESIS_SHIFT);
}
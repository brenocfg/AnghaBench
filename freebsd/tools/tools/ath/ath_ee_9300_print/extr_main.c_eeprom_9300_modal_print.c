#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct TYPE_3__ {int ant_ctrl_common; int ant_ctrl_common2; int* ant_ctrl_chain; int* xatten1_db; int* xatten1_margin; int* noise_floor_thresh_ch; int* spur_chans; int temp_slope; int voltSlope; int quick_drop; int xpa_bias_lvl; int tx_frame_to_data_start; int tx_frame_to_pa_on; int tx_end_to_xpa_off; int txEndToRxOn; int tx_frame_to_xpa_on; int txClip; int antenna_gain; int switchSettling; int adcDesiredSize; int thresh62; int paprd_rate_mask_ht20; int paprd_rate_mask_ht40; int switchcomspdt; int xLNA_bias_strength; int rf_gain_cap; int tx_gain_cap; } ;
typedef  TYPE_1__ OSPREY_MODAL_EEP_HEADER ;

/* Variables and functions */
 int MAX_MODAL_FUTURE ; 
 int MAX_MODAL_RESERVED ; 
 int OSPREY_EEPROM_MODAL_SPURS ; 
 int OSPREY_MAX_CHAINS ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
eeprom_9300_modal_print(const OSPREY_MODAL_EEP_HEADER *m)
{
	int i;

	printf("| AntCtrl: 0x%08x AntCtrl2: 0x%08x |\n",
	    m->ant_ctrl_common,
	    m->ant_ctrl_common2);

	for (i = 0; i < OSPREY_MAX_CHAINS; i++) {
		printf("| Ch %d: AntCtrl: 0x%08x Atten1: %d, atten1_margin: %d, NfThresh: %d |\n",
		    i,
		    m->ant_ctrl_chain[i],
		    m->xatten1_db[i],
		    m->xatten1_margin[i],
		    m->noise_floor_thresh_ch[i]);
	}

	printf("| Spur: ");
	for (i = 0; i < OSPREY_EEPROM_MODAL_SPURS; i++) {
		printf("(%d: %d) ", i, m->spur_chans[i]);
	}
	printf("|\n");

	printf("| TempSlope: %d, VoltSlope: %d, QuickDrop: %d, XpaBiasLvl %d |\n",
	    m->temp_slope,
	    m->voltSlope,
	    m->quick_drop,
	    m->xpa_bias_lvl);

	printf("| txFrameToDataStart: %d, TxFrameToPaOn: %d, TxEndToXpaOff: %d, TxEndToRxOn: %d, TxFrameToXpaOn: %d |\n",
	    m->tx_frame_to_data_start,
	    m->tx_frame_to_pa_on,
	    m->tx_end_to_xpa_off,
	    m->txEndToRxOn,
	    m->tx_frame_to_xpa_on);

	printf("| txClip: %d, AntGain: %d, SwitchSettling: %d, adcDesiredSize: %d |\n",
	    m->txClip,
	    m->antenna_gain,
	    m->switchSettling,
	    m->adcDesiredSize);

	printf("| Thresh62: %d, PaprdMaskHt20: 0x%08x, PaPrdMaskHt40: 0x%08x |\n",
	    m->thresh62,
	    m->paprd_rate_mask_ht20,
	    m->paprd_rate_mask_ht40);

	printf("| SwitchComSpdt: %02x, XlnaBiasStrength: %d, RfGainCap: %d, TxGainCap: %x\n",
	    m->switchcomspdt,
	    m->xLNA_bias_strength,
	    m->rf_gain_cap,
	    m->tx_gain_cap);

#if 0
    u_int8_t   reserved[MAX_MODAL_RESERVED];
    u_int16_t  switchcomspdt;
    u_int8_t   xLNA_bias_strength;                      // bit: 0,1:chain0, 2,3:chain1, 4,5:chain2
    u_int8_t   rf_gain_cap;
    u_int8_t   tx_gain_cap;                             // bit0:4 txgain cap, txgain index for max_txgain + 20 (10dBm higher than max txgain)
    u_int8_t   futureModal[MAX_MODAL_FUTURE];
    // last 12 bytes stolen and moved to newly created base extension structure
#endif
}
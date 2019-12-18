#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_7__ {int antCtrlCommon; int switchSettling; int adcDesiredSize; int* antCtrlChain; int* antennaGainCh; int* txRxAttenCh; int* rxTxMarginCh; int* noiseFloorThreshCh; int* iqCalICh; int* iqCalQCh; int* bswAtten; int* bswMargin; int txEndToXpaOff; int txEndToRxOn; int txFrameToXpaOn; int thresh62; int xpdGain; int xpd; int pdGainOverlap; int xpaBiasLvl; int txFrameToDataStart; int txFrameToPaOn; int ht40PowerIncForPdadc; int swSettleHt40; int version; int db1; int db2; int ob_cck; int ob_psk; int ob_qam; int ob_pal_off; int* futureModal; TYPE_2__* spurChans; } ;
struct TYPE_5__ {TYPE_3__ modalHeader; } ;
struct TYPE_8__ {TYPE_1__ ee_base; } ;
struct TYPE_6__ {int spurChan; scalar_t__ spurRangeHigh; scalar_t__ spurRangeLow; } ;
typedef  TYPE_3__ MODAL_EEP_9287_HEADER ;
typedef  TYPE_4__ HAL_EEPROM_9287 ;

/* Variables and functions */
 int AR5416_EEPROM_MODAL_SPURS ; 
 int AR9287_MAX_CHAINS ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
eeprom_9287_modal_print(uint16_t *buf)
{
	HAL_EEPROM_9287 *eep = (HAL_EEPROM_9287 *) buf;
	MODAL_EEP_9287_HEADER *mh = &eep->ee_base.modalHeader;
	int i;

	printf("| antCtrlCommon: 0x%.8x |\n", mh->antCtrlCommon);
	printf("| switchSettling: 0x%.2x |\n", mh->switchSettling);
	printf("| adcDesiredSize: %d |\n", mh->adcDesiredSize);

	for (i = 0; i < AR9287_MAX_CHAINS; i++) {
		printf("| Chain %d:\n", i);
		printf("| antCtrlChain:        0:0x%.4x |\n", mh->antCtrlChain[i]);
		printf("| antennaGainCh:       0:0x%.2x |\n", mh->antennaGainCh[i]);
		printf("| txRxAttenCh:         0:0x%.2x |\n", mh->txRxAttenCh[i]);
		printf("| rxTxMarginCh:        0:0x%.2x |\n", mh->rxTxMarginCh[i]);
		printf("| noiseFloorThresCh:   0:0x%.2x |\n", mh->noiseFloorThreshCh[i]);
		printf("| iqCalICh:            0:0x%.2x |\n", mh->iqCalICh[i]);
		printf("| iqCalQCh:            0:0x%.2x |\n", mh->iqCalQCh[i]);
		printf("| bswAtten:            0:0x%.2x |\n", mh->bswAtten[i]);
		printf("| bswMargin:           0:0x%.2x |\n", mh->bswMargin[i]);
		printf("\n");
	}

	printf("| txEndToXpaOff: 0x%.2x | txEndToRxOn: 0x%.2x | txFrameToXpaOn: 0x%.2x |\n",
	    mh->txEndToXpaOff, mh->txEndToRxOn, mh->txFrameToXpaOn);
	printf("| thres62: 0x%.2x\n", mh->thresh62);
	printf("| xpdGain: 0x%.2x | xpd: 0x%.2x |\n", mh->xpdGain, mh->xpd);

	printf("| pdGainOverlap: 0x%.2x xpaBiasLvl: 0x%.2x |\n", mh->pdGainOverlap, mh->xpaBiasLvl);
	printf("| txFrameToDataStart: 0x%.2x | txFrameToPaOn: 0x%.2x |\n", mh->txFrameToDataStart, mh->txFrameToPaOn);
	printf("| ht40PowerIncForPdadc: 0x%.2x |\n", mh->ht40PowerIncForPdadc);
	printf("| swSettleHt40: 0x%.2x |\n", mh->swSettleHt40);

	printf("| Modal Version: %.2x |\n", mh->version);
	printf("| db1 = %d | db2 = %d |\n", mh->db1, mh->db2);
	printf("| ob_cck = %d | ob_psk = %d | ob_qam = %d | ob_pal_off = %d |\n",
	    mh->ob_cck, mh->ob_psk, mh->ob_qam, mh->ob_pal_off);

	printf("| futureModal: ");
	for (i = 0; i < sizeof(mh->futureModal) / sizeof(uint16_t); i++) {
	    printf("0x%.2x ", mh->futureModal[i]);
	}
	printf("\n");

	/* and now, spur channels */
	for (i = 0; i < AR5416_EEPROM_MODAL_SPURS; i++) {
		printf("| Spur %d: spurChan: 0x%.4x spurRangeLow: 0x%.2x spurRangeHigh: 0x%.2x |\n",
		    i, mh->spurChans[i].spurChan,
		    (int) mh->spurChans[i].spurRangeLow,
		    (int) mh->spurChans[i].spurRangeHigh);
	}
}
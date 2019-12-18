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
struct TYPE_6__ {TYPE_3__* modalHeader; } ;
struct TYPE_8__ {TYPE_2__ ee_base; } ;
struct TYPE_7__ {int antCtrlCommon; int switchSettling; int adcDesiredSize; int* antCtrlChain; int* antennaGainCh; int* txRxAttenCh; int* rxTxMarginCh; int* noiseFloorThreshCh; int* xlnaGainCh; int* iqCalICh; int* iqCalQCh; int* bswAtten; int* bswMargin; int* xatten2Db; int* xatten2Margin; int txEndToXpaOff; int txEndToRxOn; int txFrameToXpaOn; int thresh62; int xpdGain; int xpd; int* xpaBiasLvlFreq; int pdGainOverlap; int ob; int db; int xpaBiasLvl; int pwrDecreaseFor2Chain; int pwrDecreaseFor3Chain; int txFrameToDataStart; int txFrameToPaOn; int ht40PowerIncForPdadc; int swSettleHt40; int ob_ch1; int db_ch1; int flagBits; int miscBits; int* futureModal; TYPE_1__* spurChans; scalar_t__ pgaDesiredSize; } ;
struct TYPE_5__ {int spurChan; scalar_t__ spurRangeHigh; scalar_t__ spurRangeLow; } ;
typedef  TYPE_3__ MODAL_EEP_HEADER ;
typedef  TYPE_4__ HAL_EEPROM_v14 ;

/* Variables and functions */
 int AR5416_EEPROM_MODAL_SPURS ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static void
eeprom_v14_modal_print(uint16_t *buf, int m)
{
	HAL_EEPROM_v14 *eep = (HAL_EEPROM_v14 *) buf;
	MODAL_EEP_HEADER *mh = &eep->ee_base.modalHeader[m];
	int i;

	printf("| antCtrlCommon: 0x%.8x |\n", mh->antCtrlCommon);
	printf("| switchSettling: 0x%.2x |\n", mh->switchSettling);
	printf("| adcDesiredSize: %d |\n| pgaDesiredSize: %.2f dBm |\n",
	    mh->adcDesiredSize, (float) mh->pgaDesiredSize / 2.0);

	printf("| antCtrlChain:        0:0x%.8x 1:0x%.8x 2:0x%.8x |\n",
	    mh->antCtrlChain[0], mh->antCtrlChain[1], mh->antCtrlChain[2]);
	printf("| antennaGainCh:       0:0x%.2x   1:0x%.2x   2:0x%.2x   |\n",
	    mh->antennaGainCh[0], mh->antennaGainCh[1], mh->antennaGainCh[2]);
	printf("| txRxAttenCh:         0:0x%.2x   1:0x%.2x   2:0x%.2x   |\n",
	    mh->txRxAttenCh[0], mh->txRxAttenCh[1], mh->txRxAttenCh[2]);
	printf("| rxTxMarginCh:        0:0x%.2x   1:0x%.2x   2:0x%.2x   |\n",
	    mh->rxTxMarginCh[0], mh->rxTxMarginCh[1], mh->rxTxMarginCh[2]);
 	printf("| noiseFloorThresCh:   0:0x%.2x   1:0x%.2x   2:0x%.2x   |\n",
	    mh->noiseFloorThreshCh[0], mh->noiseFloorThreshCh[1], mh->noiseFloorThreshCh[2]);
	printf("| xlnaGainCh:          0:0x%.2x   1:0x%.2x   2:0x%.2x   |\n",
	    mh->xlnaGainCh[0], mh->xlnaGainCh[1], mh->xlnaGainCh[2]);
	printf("| iqCalICh:            0:0x%.2x   1:0x%.2x   2:0x%.2x   |\n| iqCalQCh:            0:0x%.2x   1:0x%.2x   2:0x%.2x   |\n",
	    mh->iqCalICh[0], mh->iqCalICh[1], mh->iqCalICh[2],
	    mh->iqCalQCh[0], mh->iqCalQCh[1], mh->iqCalQCh[2]);
	printf("| bswAtten:            0:0x%.2x   1:0x%.2x   2:0x%.2x   |\n",
	    mh->bswAtten[0], mh->bswAtten[1], mh->bswAtten[2]);
	printf("| bswMargin:           0:0x%.2x   1:0x%.2x   2:0x%.2x   |\n",
	    mh->bswMargin[0], mh->bswMargin[1], mh->bswMargin[2]);
	printf("| xatten2Db:           0:0x%.2x   1:0x%.2x   2:0x%.2x   |\n",
	    mh->xatten2Db[0], mh->xatten2Db[1], mh->xatten2Db[2]);
	printf("| xatten2Margin:       0:0x%.2x   1:0x%.2x   2:0x%.2x   |\n",
	    mh->xatten2Margin[0], mh->xatten2Margin[1], mh->xatten2Margin[2]);

	printf("| txEndToXpaOff: 0x%.2x | txEndToRxOn: 0x%.2x | txFrameToXpaOn: 0x%.2x |\n",
	    mh->txEndToXpaOff, mh->txEndToRxOn, mh->txFrameToXpaOn);

	printf("| thres62: 0x%.2x\n", mh->thresh62);

	printf("| xpdGain: 0x%.2x | xpd: 0x%.2x |\n", mh->xpdGain, mh->xpd);
	printf("| xpaBiasLvlFreq: 0:0x%.4x 1:0x%.4x 2:0x%.4x |\n",
	    mh->xpaBiasLvlFreq[0], mh->xpaBiasLvlFreq[1], mh->xpaBiasLvlFreq[2]);

	printf("| pdGainOverlap: 0x%.2x | ob: 0x%.2x | db: 0x%.2x | xpaBiasLvl: 0x%.2x |\n",
	    mh->pdGainOverlap, mh->ob, mh->db, mh->xpaBiasLvl);

	printf("| pwrDecreaseFor2Chain: 0x%.2x | pwrDecreaseFor3Chain: 0x%.2x | txFrameToDataStart: 0x%.2x | txFrameToPaOn: 0x%.2x |\n",
	    mh->pwrDecreaseFor2Chain, mh->pwrDecreaseFor3Chain, mh->txFrameToDataStart,
	    mh->txFrameToPaOn);

	printf("| ht40PowerIncForPdadc: 0x%.2x |\n", mh->ht40PowerIncForPdadc);

	printf("| swSettleHt40: 0x%.2x |\n", mh->swSettleHt40);

	printf("| ob_ch1: 0x%.2x | db_ch1: 0x%.2x |\n", mh->ob_ch1, mh->db_ch1);

	printf("| flagBits: 0x%.2x | miscBits: 0x%.2x |\n", mh->flagBits, mh->miscBits);


	printf("| futureModal: 0x%.2x 0x%.2x 0x%.2x 0x%.2x 0x%.2x 0x%.2x |\n",
	    mh->futureModal[0],
	    mh->futureModal[1],
	    mh->futureModal[2],
	    mh->futureModal[3],
	    mh->futureModal[4],
	    mh->futureModal[5]);

	/* and now, spur channels */
	for (i = 0; i < AR5416_EEPROM_MODAL_SPURS; i++) {
		printf("| Spur %d: spurChan: 0x%.4x spurRangeLow: 0x%.2x spurRangeHigh: 0x%.2x |\n",
		    i, mh->spurChans[i].spurChan,
		    (int) mh->spurChans[i].spurRangeLow,
		    (int) mh->spurChans[i].spurRangeHigh);
	}
}
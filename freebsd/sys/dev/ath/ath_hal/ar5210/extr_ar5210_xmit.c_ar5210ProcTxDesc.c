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
struct ath_tx_status {int ts_seqnum; scalar_t__ ts_finaltsi; scalar_t__ ts_antenna; void* ts_longretry; void* ts_shortretry; void* ts_rssi; void* ts_rate; int /*<<< orphan*/  ts_status; void* ts_tstamp; } ;
struct ath_hal {int dummy; } ;
struct ath_desc {int dummy; } ;
struct ar5210_desc {int ds_status1; int ds_status0; int ds_ctl0; } ;
typedef  int /*<<< orphan*/  HAL_STATUS ;

/* Variables and functions */
 struct ar5210_desc* AR5210DESC (struct ath_desc*) ; 
 int /*<<< orphan*/  AR_AckSigStrength ; 
 int AR_Done ; 
 int AR_ExcessiveRetries ; 
 int AR_FIFOUnderrun ; 
 int AR_Filtered ; 
 int AR_FrmXmitOK ; 
 int /*<<< orphan*/  AR_LongRetryCnt ; 
 int /*<<< orphan*/  AR_SendTimestamp ; 
 int AR_SeqNum ; 
 int /*<<< orphan*/  AR_ShortRetryCnt ; 
 int /*<<< orphan*/  AR_XmitRate ; 
 int /*<<< orphan*/  HAL_EINPROGRESS ; 
 int /*<<< orphan*/  HAL_OK ; 
 int /*<<< orphan*/  HAL_TXERR_FIFO ; 
 int /*<<< orphan*/  HAL_TXERR_FILT ; 
 int /*<<< orphan*/  HAL_TXERR_XRETRY ; 
 void* MS (int,int /*<<< orphan*/ ) ; 

HAL_STATUS
ar5210ProcTxDesc(struct ath_hal *ah,
	struct ath_desc *ds, struct ath_tx_status *ts)
{
	struct ar5210_desc *ads = AR5210DESC(ds);

	if ((ads->ds_status1 & AR_Done) == 0)
		return HAL_EINPROGRESS;

	/* Update software copies of the HW status */
	ts->ts_seqnum = ads->ds_status1 & AR_SeqNum;
	ts->ts_tstamp = MS(ads->ds_status0, AR_SendTimestamp);
	ts->ts_status = 0;
	if ((ads->ds_status0 & AR_FrmXmitOK) == 0) {
		if (ads->ds_status0 & AR_ExcessiveRetries)
			ts->ts_status |= HAL_TXERR_XRETRY;
		if (ads->ds_status0 & AR_Filtered)
			ts->ts_status |= HAL_TXERR_FILT;
		if (ads->ds_status0  & AR_FIFOUnderrun)
			ts->ts_status |= HAL_TXERR_FIFO;
	}
	ts->ts_rate = MS(ads->ds_ctl0, AR_XmitRate);
	ts->ts_rssi = MS(ads->ds_status1, AR_AckSigStrength);
	ts->ts_shortretry = MS(ads->ds_status0, AR_ShortRetryCnt);
	ts->ts_longretry = MS(ads->ds_status0, AR_LongRetryCnt);
	ts->ts_antenna = 0;		/* NB: don't know */
	ts->ts_finaltsi = 0;

	return HAL_OK;
}
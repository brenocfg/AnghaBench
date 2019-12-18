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
struct ath_rx_status {int rs_datalen; int rs_tstamp; int rs_phyerr; int rs_antenna; int rs_more; void* rs_rate; void* rs_keyix; void* rs_rssi; int /*<<< orphan*/  rs_status; } ;
struct ath_hal {int dummy; } ;
struct ath_desc {int dummy; } ;
struct ar5210_desc {int ds_status1; int ds_status0; } ;
typedef  int /*<<< orphan*/  HAL_STATUS ;

/* Variables and functions */
 struct ar5210_desc* AR5210DESC (struct ath_desc*) ; 
 int AR_CRCErr ; 
 int AR_DataLen ; 
 int AR_DecryptCRCErr ; 
 int AR_Done ; 
 int AR_FIFOOverrun ; 
 int AR_FrmRcvOK ; 
 int /*<<< orphan*/  AR_KeyIdx ; 
 int AR_KeyIdxValid ; 
 int AR_More ; 
 int AR_PHYErr ; 
 int AR_PHYErr_S ; 
 int /*<<< orphan*/  AR_RXDP ; 
 int AR_RcvAntenna ; 
 int /*<<< orphan*/  AR_RcvRate ; 
 int /*<<< orphan*/  AR_RcvSigStrength ; 
 int /*<<< orphan*/  AR_RcvTimestamp ; 
 int /*<<< orphan*/  AR_TSF_L32 ; 
 int /*<<< orphan*/  HAL_EINPROGRESS ; 
 int /*<<< orphan*/  HAL_OK ; 
 int /*<<< orphan*/  HAL_RXERR_CRC ; 
 int /*<<< orphan*/  HAL_RXERR_DECRYPT ; 
 int /*<<< orphan*/  HAL_RXERR_FIFO ; 
 int /*<<< orphan*/  HAL_RXERR_PHY ; 
 void* HAL_RXKEYIX_INVALID ; 
 void* MS (int,int /*<<< orphan*/ ) ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 

HAL_STATUS
ar5210ProcRxDesc(struct ath_hal *ah, struct ath_desc *ds,
	uint32_t pa, struct ath_desc *nds, uint64_t tsf,
	struct ath_rx_status *rs)
{
	struct ar5210_desc *ads = AR5210DESC(ds);
	struct ar5210_desc *ands = AR5210DESC(nds);
	uint32_t now, rstamp;

	if ((ads->ds_status1 & AR_Done) == 0)
		return HAL_EINPROGRESS;
	/*
	 * Given the use of a self-linked tail be very sure that the hw is
	 * done with this descriptor; the hw may have done this descriptor
	 * once and picked it up again...make sure the hw has moved on.
	 */
	if ((ands->ds_status1 & AR_Done) == 0 && OS_REG_READ(ah, AR_RXDP) == pa)
		return HAL_EINPROGRESS;

	rs->rs_datalen = ads->ds_status0 & AR_DataLen;
	rstamp = MS(ads->ds_status1, AR_RcvTimestamp);
	/*
	 * Convert timestamp.  The value in the
	 * descriptor is bits [10..22] of the TSF.
	 */
	now = (OS_REG_READ(ah, AR_TSF_L32) >> 10) & 0xffff;
	if ((now & 0x1fff) < rstamp)
		rstamp |= (now - 0x2000) & 0xffff;
	else
		rstamp |= now;
	/* NB: keep only 15 bits for consistency w/ other chips */
	rs->rs_tstamp = rstamp & 0x7fff;
	rs->rs_status = 0;
	if ((ads->ds_status1 & AR_FrmRcvOK) == 0) {
		if (ads->ds_status1 & AR_CRCErr)
			rs->rs_status |= HAL_RXERR_CRC;
		else if (ads->ds_status1 & AR_DecryptCRCErr)
			rs->rs_status |= HAL_RXERR_DECRYPT;
		else if (ads->ds_status1 & AR_FIFOOverrun)
			rs->rs_status |= HAL_RXERR_FIFO;
		else {
			rs->rs_status |= HAL_RXERR_PHY;
			rs->rs_phyerr =
				(ads->ds_status1 & AR_PHYErr) >> AR_PHYErr_S;
		}
	}
	/* XXX what about KeyCacheMiss? */
	rs->rs_rssi = MS(ads->ds_status0, AR_RcvSigStrength);
	if (ads->ds_status1 & AR_KeyIdxValid)
		rs->rs_keyix = MS(ads->ds_status1, AR_KeyIdx);
	else
		rs->rs_keyix = HAL_RXKEYIX_INVALID;
	/* NB: caller expected to do rate table mapping */
	rs->rs_rate = MS(ads->ds_status0, AR_RcvRate);
	rs->rs_antenna  = (ads->ds_status0 & AR_RcvAntenna) ? 1 : 0;
	rs->rs_more = (ads->ds_status0 & AR_More) ? 1 : 0;

	return HAL_OK;
}
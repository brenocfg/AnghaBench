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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ u_int ;
struct ath_hal {int dummy; } ;
struct ath_desc {int dummy; } ;
struct ar5210_desc {scalar_t__ ds_ctl1; scalar_t__ ds_ctl0; } ;
typedef  int HAL_PKT_TYPE ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_TRUE ; 
 struct ar5210_desc* AR5210DESC (struct ath_desc*) ; 
 scalar_t__ AR_AntModeXmit ; 
 scalar_t__ AR_ClearDestMask ; 
 scalar_t__ AR_EncryptKeyIdx ; 
 scalar_t__ AR_EncryptKeyIdx_S ; 
 scalar_t__ AR_EncryptKeyValid ; 
 scalar_t__ AR_FrameLen ; 
 scalar_t__ AR_Frm_NoDelay ; 
 scalar_t__ AR_HdrLen ; 
 scalar_t__ AR_HdrLen_S ; 
 scalar_t__ AR_RTSCTSEnable ; 
 scalar_t__ AR_RTSDuration ; 
 scalar_t__ AR_RTSDuration_S ; 
 scalar_t__ AR_TxInterReq ; 
 scalar_t__ AR_XmitRate_S ; 
 int /*<<< orphan*/  HALASSERT (int) ; 
 int HAL_PKT_TYPE_BEACON ; 
 int HAL_PKT_TYPE_PROBE_RESP ; 
 scalar_t__ HAL_TXDESC_CLRDMASK ; 
 scalar_t__ HAL_TXDESC_INTREQ ; 
 scalar_t__ HAL_TXDESC_RTSENA ; 
 scalar_t__ HAL_TXKEYIX_INVALID ; 
 int isValidPktType (int) ; 
 int isValidTxRate (scalar_t__) ; 

HAL_BOOL
ar5210SetupTxDesc(struct ath_hal *ah, struct ath_desc *ds,
	u_int pktLen,
	u_int hdrLen,
	HAL_PKT_TYPE type,
	u_int txPower,
	u_int txRate0, u_int txTries0,
	u_int keyIx,
	u_int antMode,
	u_int flags,
	u_int rtsctsRate,
	u_int rtsctsDuration,
        u_int compicvLen,
	u_int compivLen,
	u_int comp)
{
	struct ar5210_desc *ads = AR5210DESC(ds);
	uint32_t frtype;

	(void) txPower;
	(void) rtsctsDuration;

	HALASSERT(txTries0 != 0);
	HALASSERT(isValidPktType(type));
	HALASSERT(isValidTxRate(txRate0));

	if (type == HAL_PKT_TYPE_BEACON || type == HAL_PKT_TYPE_PROBE_RESP)
		frtype = AR_Frm_NoDelay;
	else
		frtype = type << 26;
	ads->ds_ctl0 = (pktLen & AR_FrameLen)
		     | (txRate0 << AR_XmitRate_S)
		     | ((hdrLen << AR_HdrLen_S) & AR_HdrLen)
		     | frtype
		     | (flags & HAL_TXDESC_CLRDMASK ? AR_ClearDestMask : 0)
		     | (flags & HAL_TXDESC_INTREQ ? AR_TxInterReq : 0)
		     | (antMode ? AR_AntModeXmit : 0)
		     ;
	if (keyIx != HAL_TXKEYIX_INVALID) {
		ads->ds_ctl1 = (keyIx << AR_EncryptKeyIdx_S) & AR_EncryptKeyIdx;
		ads->ds_ctl0 |= AR_EncryptKeyValid;
	} else
		ads->ds_ctl1 = 0;
	if (flags & HAL_TXDESC_RTSENA) {
		ads->ds_ctl0 |= AR_RTSCTSEnable;
		ads->ds_ctl1 |= (rtsctsDuration << AR_RTSDuration_S)
		    & AR_RTSDuration;
	}
	return AH_TRUE;
}
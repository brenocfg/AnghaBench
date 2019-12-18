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
typedef  scalar_t__ u_int ;
struct ath_hal {int dummy; } ;
struct ath_desc {int dummy; } ;
struct ar5211_desc {int ds_ctl1; scalar_t__ ds_ctl0; } ;
typedef  int HAL_PKT_TYPE ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_TRUE ; 
 struct ar5211_desc* AR5211DESC (struct ath_desc*) ; 
 scalar_t__ AR_AntModeXmit_S ; 
 scalar_t__ AR_ClearDestMask ; 
 scalar_t__ AR_EncryptKeyIdx ; 
 scalar_t__ AR_EncryptKeyIdx_S ; 
 scalar_t__ AR_EncryptKeyValid ; 
 scalar_t__ AR_FrameLen ; 
 int AR_NoAck ; 
 scalar_t__ AR_RTSCTSEnable ; 
 scalar_t__ AR_TxInterReq ; 
 scalar_t__ AR_VEOL ; 
 scalar_t__ AR_XmitRate_S ; 
 int /*<<< orphan*/  HALASSERT (int) ; 
 scalar_t__ HAL_TXDESC_CLRDMASK ; 
 scalar_t__ HAL_TXDESC_INTREQ ; 
 scalar_t__ HAL_TXDESC_NOACK ; 
 scalar_t__ HAL_TXDESC_RTSENA ; 
 scalar_t__ HAL_TXDESC_VEOL ; 
 scalar_t__ HAL_TXKEYIX_INVALID ; 
 int isValidPktType (int) ; 
 int isValidTxRate (scalar_t__) ; 

HAL_BOOL
ar5211SetupTxDesc(struct ath_hal *ah, struct ath_desc *ds,
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
	struct ar5211_desc *ads = AR5211DESC(ds);

	(void) hdrLen;
	(void) txPower;
	(void) rtsctsRate; (void) rtsctsDuration;

	HALASSERT(txTries0 != 0);
	HALASSERT(isValidPktType(type));
	HALASSERT(isValidTxRate(txRate0));
	/* XXX validate antMode */

	ads->ds_ctl0 = (pktLen & AR_FrameLen)
		     | (txRate0 << AR_XmitRate_S)
		     | (antMode << AR_AntModeXmit_S)
		     | (flags & HAL_TXDESC_CLRDMASK ? AR_ClearDestMask : 0)
		     | (flags & HAL_TXDESC_INTREQ ? AR_TxInterReq : 0)
		     | (flags & HAL_TXDESC_RTSENA ? AR_RTSCTSEnable : 0)
		     | (flags & HAL_TXDESC_VEOL ? AR_VEOL : 0)
		     ;
	ads->ds_ctl1 = (type << 26)
		     | (flags & HAL_TXDESC_NOACK ? AR_NoAck : 0)
		     ;

	if (keyIx != HAL_TXKEYIX_INVALID) {
		ads->ds_ctl1 |=
			(keyIx << AR_EncryptKeyIdx_S) & AR_EncryptKeyIdx;
		ads->ds_ctl0 |= AR_EncryptKeyValid;
	}
	return AH_TRUE;
#undef RATE
}
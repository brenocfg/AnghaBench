#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct TYPE_3__ {scalar_t__ ath_hal_min_gainidx; scalar_t__ ath_hal_ext_atten_margin_cfg; } ;
struct ath_hal {TYPE_1__ ah_config; } ;
struct TYPE_4__ {int ah_rx_chainmask; int ah_tx_chainmask; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 TYPE_2__* AH9300 (struct ath_hal*) ; 
 int AR_PHY_EXT_ATTEN_CTL_0 ; 
 int AR_PHY_EXT_ATTEN_CTL_1 ; 
 int AR_PHY_EXT_ATTEN_CTL_2 ; 
 int /*<<< orphan*/  AR_PHY_EXT_ATTEN_CTL_XATTEN1_DB ; 
 int /*<<< orphan*/  AR_PHY_EXT_ATTEN_CTL_XATTEN1_MARGIN ; 
 scalar_t__ AR_SREV_JUPITER (struct ath_hal*) ; 
 scalar_t__ AR_SREV_POSEIDON (struct ath_hal*) ; 
 int /*<<< orphan*/  OS_REG_RMW_FIELD (struct ath_hal*,int,int /*<<< orphan*/ ,int) ; 
 int ar9300_attenuation_chain_get (struct ath_hal*,int,int /*<<< orphan*/ ) ; 
 int ar9300_attenuation_margin_chain_get (struct ath_hal*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ar9300_rx_gain_index_get (struct ath_hal*) ; 

HAL_BOOL
ar9300_attenuation_apply(struct ath_hal *ah, u_int16_t channel)
{
	int i;
	uint32_t value;
	uint32_t ext_atten_reg[3] = {
	    AR_PHY_EXT_ATTEN_CTL_0,
	    AR_PHY_EXT_ATTEN_CTL_1,
	    AR_PHY_EXT_ATTEN_CTL_2
	};

	/*
	 * If it's an AR9462 and we're receiving on the second
	 * chain only, set the chain 0 details from chain 1
	 * calibration.
	 *
	 * This is from ath9k.
	 */
	if (AR_SREV_JUPITER(ah) && (AH9300(ah)->ah_rx_chainmask == 0x2)) {
		value = ar9300_attenuation_chain_get(ah, 1, channel);
		OS_REG_RMW_FIELD(ah, ext_atten_reg[0],
		    AR_PHY_EXT_ATTEN_CTL_XATTEN1_DB, value);
		value = ar9300_attenuation_margin_chain_get(ah, 1, channel);
		OS_REG_RMW_FIELD(ah, ext_atten_reg[0],
		    AR_PHY_EXT_ATTEN_CTL_XATTEN1_MARGIN, value);
	}

	/*
	 * Now, loop over the configured transmit chains and
	 * load in the attenuation/margin settings as appropriate.
	 */
	for (i = 0; i < 3; i++) {
		if ((AH9300(ah)->ah_tx_chainmask & (1 << i)) == 0)
			continue;

		value = ar9300_attenuation_chain_get(ah, i, channel);
		OS_REG_RMW_FIELD(ah, ext_atten_reg[i],
		    AR_PHY_EXT_ATTEN_CTL_XATTEN1_DB,
		    value);

		if (AR_SREV_POSEIDON(ah) &&
		    (ar9300_rx_gain_index_get(ah) == 0) &&
		    ah->ah_config.ath_hal_ext_atten_margin_cfg) {
			value = 5;
		} else {
			value = ar9300_attenuation_margin_chain_get(ah, 0,
			    channel);
		}

		/*
		 * I'm not sure why it's loading in this setting into
		 * the chain 0 margin regardless of the current chain.
		 */
		if (ah->ah_config.ath_hal_min_gainidx)
			OS_REG_RMW_FIELD(ah,
			    AR_PHY_EXT_ATTEN_CTL_0,
			    AR_PHY_EXT_ATTEN_CTL_XATTEN1_MARGIN,
			    value);

		OS_REG_RMW_FIELD(ah,
		    ext_atten_reg[i],
		    AR_PHY_EXT_ATTEN_CTL_XATTEN1_MARGIN,
		    value);
	}

	return (0);
}
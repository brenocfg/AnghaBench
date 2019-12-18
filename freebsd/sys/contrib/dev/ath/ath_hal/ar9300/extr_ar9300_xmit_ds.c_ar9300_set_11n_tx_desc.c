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
typedef  int u_int ;
struct ath_hal_9300 {scalar_t__ ah_tx_power_index_offset; } ;
struct ath_hal {int dummy; } ;
struct ar9300_txc {int ds_ctl11; int ds_ctl12; int ds_ctl17; scalar_t__ ds_ctl22; scalar_t__ ds_ctl21; scalar_t__ ds_ctl20; int /*<<< orphan*/  ds_ctl19; scalar_t__ ds_ctl18; } ;
typedef  int HAL_PKT_TYPE ;
typedef  int HAL_KEY_TYPE ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 struct ar9300_txc* AR9300TXC (void*) ; 
 int AR_clr_dest_mask ; 
 int /*<<< orphan*/  AR_dest_idx ; 
 int AR_dest_idx_valid ; 
 int /*<<< orphan*/  AR_encr_type ; 
 int AR_ext_and_ctl ; 
 int AR_ext_only ; 
 int AR_frame_len ; 
 int /*<<< orphan*/  AR_frame_type ; 
 int AR_insert_ts ; 
 int AR_ldpc ; 
 int AR_loc_mode ; 
 int AR_low_rx_chain ; 
 int AR_no_ack ; 
 int /*<<< orphan*/  AR_not_sounding ; 
 int AR_veol ; 
 int AR_virt_more_frag ; 
 int /*<<< orphan*/  AR_xmit_power0 ; 
 int /*<<< orphan*/  HALASSERT (int /*<<< orphan*/ ) ; 
 int HAL_TXDESC_CLRDMASK ; 
 int HAL_TXDESC_EXT_AND_CTL ; 
 int HAL_TXDESC_EXT_ONLY ; 
 int HAL_TXDESC_HWTS ; 
 int HAL_TXDESC_LDPC ; 
 int HAL_TXDESC_LOWRXCHAIN ; 
 int HAL_TXDESC_NOACK ; 
 int HAL_TXDESC_POS ; 
 int HAL_TXDESC_VEOL ; 
 int HAL_TXDESC_VMF ; 
 int HAL_TXKEYIX_INVALID ; 
 int SM (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_key_type (int) ; 
 int /*<<< orphan*/  is_valid_pkt_type (int) ; 

void
ar9300_set_11n_tx_desc(
    struct ath_hal *ah,
    void *ds,
    u_int pkt_len,
    HAL_PKT_TYPE type,
    u_int tx_power,
    u_int key_ix,
    HAL_KEY_TYPE key_type,
    u_int flags)
{
    struct ar9300_txc *ads = AR9300TXC(ds);
    struct ath_hal_9300 *ahp = AH9300(ah);

    HALASSERT(is_valid_pkt_type(type));
    HALASSERT(is_valid_key_type(key_type));

    tx_power += ahp->ah_tx_power_index_offset;
    if (tx_power > 63) {
        tx_power = 63;
    }
    ads->ds_ctl11 =
        (pkt_len & AR_frame_len)
      | (flags & HAL_TXDESC_VMF ? AR_virt_more_frag : 0)
      | SM(tx_power, AR_xmit_power0)
      | (flags & HAL_TXDESC_VEOL ? AR_veol : 0)
      | (flags & HAL_TXDESC_CLRDMASK ? AR_clr_dest_mask : 0)
      | (key_ix != HAL_TXKEYIX_INVALID ? AR_dest_idx_valid : 0)
      | (flags & HAL_TXDESC_LOWRXCHAIN ? AR_low_rx_chain : 0);

    ads->ds_ctl12 =
        (key_ix != HAL_TXKEYIX_INVALID ? SM(key_ix, AR_dest_idx) : 0)
      | SM(type, AR_frame_type)
      | (flags & HAL_TXDESC_NOACK ? AR_no_ack : 0)
      | (flags & HAL_TXDESC_HWTS ? AR_insert_ts : 0)
      | (flags & HAL_TXDESC_EXT_ONLY ? AR_ext_only : 0)
      | (flags & HAL_TXDESC_EXT_AND_CTL ? AR_ext_and_ctl : 0);

    ads->ds_ctl17 =
        SM(key_type, AR_encr_type) | (flags & HAL_TXDESC_LDPC ? AR_ldpc : 0);

    ads->ds_ctl18 = 0;
    ads->ds_ctl19 = AR_not_sounding; /* set not sounding for normal frame */

    /* ToA/ToD positioning */
    if (flags & HAL_TXDESC_POS) {
        ads->ds_ctl12 |= AR_loc_mode;
        ads->ds_ctl19 &= ~AR_not_sounding;
    }

    /*
     * Clear Ness1/2/3 (Number of Extension Spatial Streams) fields.
     * Ness0 is cleared in ctl19.  See EV66059 (BB panic).
     */
    ads->ds_ctl20 = 0;
    ads->ds_ctl21 = 0;
    ads->ds_ctl22 = 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  tstamp_usec; int /*<<< orphan*/  tstamp_sec; int /*<<< orphan*/  threadid; } ;
struct if_ath_alq_payload {TYPE_1__ hdr; int /*<<< orphan*/  payload; } ;
struct ar9300_rxs {int status3; int status6; int status7; int status8; int status9; int /*<<< orphan*/  status11; int /*<<< orphan*/  status4; int /*<<< orphan*/  status2; int /*<<< orphan*/  status1; int /*<<< orphan*/  status5; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_2040 ; 
 int /*<<< orphan*/  AR_apsd_trig ; 
 int /*<<< orphan*/  AR_crc_err ; 
 int /*<<< orphan*/  AR_data_len ; 
 int /*<<< orphan*/  AR_decrypt_busy_err ; 
 int /*<<< orphan*/  AR_decrypt_crc_err ; 
 int /*<<< orphan*/  AR_gi ; 
 int /*<<< orphan*/  AR_hi_rx_chain ; 
 int /*<<< orphan*/  AR_hw_upload_data ; 
 int /*<<< orphan*/  AR_hw_upload_data_type ; 
 int /*<<< orphan*/  AR_hw_upload_data_valid ; 
 int /*<<< orphan*/  AR_key_idx ; 
 int /*<<< orphan*/  AR_key_miss ; 
 int /*<<< orphan*/  AR_michael_err ; 
 int /*<<< orphan*/  AR_num_delim ; 
 int /*<<< orphan*/  AR_parallel40 ; 
 int /*<<< orphan*/  AR_phy_err_code ; 
 int /*<<< orphan*/  AR_phyerr ; 
 int /*<<< orphan*/  AR_position_bit ; 
 int /*<<< orphan*/  AR_post_delim_crc_err ; 
 int /*<<< orphan*/  AR_pre_delim_crc_err ; 
 int /*<<< orphan*/  AR_rx_aggr ; 
 int /*<<< orphan*/  AR_rx_antenna ; 
 int /*<<< orphan*/  AR_rx_done ; 
 int /*<<< orphan*/  AR_rx_first_aggr ; 
 int /*<<< orphan*/  AR_rx_frame_ok ; 
 int /*<<< orphan*/  AR_rx_key_idx_valid ; 
 int /*<<< orphan*/  AR_rx_more ; 
 int /*<<< orphan*/  AR_rx_more_aggr ; 
 int /*<<< orphan*/  AR_rx_ness ; 
 int /*<<< orphan*/  AR_rx_not_sounding ; 
 int /*<<< orphan*/  AR_rx_rate ; 
 int /*<<< orphan*/  AR_rx_rssi_ant00 ; 
 int /*<<< orphan*/  AR_rx_rssi_ant01 ; 
 int /*<<< orphan*/  AR_rx_rssi_ant02 ; 
 int /*<<< orphan*/  AR_rx_rssi_ant10 ; 
 int /*<<< orphan*/  AR_rx_rssi_ant11 ; 
 int /*<<< orphan*/  AR_rx_rssi_ant12 ; 
 int /*<<< orphan*/  AR_rx_rssi_combined ; 
 int /*<<< orphan*/  AR_rx_stbc ; 
 int MF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ be32toh (int /*<<< orphan*/ ) ; 
 scalar_t__ be64toh (int /*<<< orphan*/ ) ; 
 int last_ts ; 
 int /*<<< orphan*/  memcpy (struct ar9300_rxs*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static void
ar9300_decode_rxstatus(struct if_ath_alq_payload *a)
{
	struct ar9300_rxs rxs;

	/* XXX assumes rxs is smaller than PAYLOAD_LEN! */
	memcpy(&rxs, &a->payload, sizeof(struct ar9300_rxs));

	printf("[%u.%06u] [%llu] RXSTATUS RxTimestamp: %u (%d)\n",
	    (unsigned int) be32toh(a->hdr.tstamp_sec),
	    (unsigned int) be32toh(a->hdr.tstamp_usec),
	    (unsigned long long) be64toh(a->hdr.threadid),
	    rxs.status3,
	    rxs.status3 - last_ts);

	/* status1 */
	/* .. and status5 */
	printf("    RSSI %d/%d/%d / %d/%d/%d; combined: %d; rate=0x%02x\n",
	    MS(rxs.status1, AR_rx_rssi_ant00),
	    MS(rxs.status1, AR_rx_rssi_ant01),
	    MS(rxs.status1, AR_rx_rssi_ant02),
	    MS(rxs.status5, AR_rx_rssi_ant10),
	    MS(rxs.status5, AR_rx_rssi_ant11),
	    MS(rxs.status5, AR_rx_rssi_ant12),
	    MS(rxs.status5, AR_rx_rssi_combined),
	    MS(rxs.status1, AR_rx_rate));

	/* status2 */
	printf("    Len: %d; more=%d, delim=%d, upload=%d\n",
	    MS(rxs.status2, AR_data_len),
	    MF(rxs.status2, AR_rx_more),
	    MS(rxs.status2, AR_num_delim),
	    MS(rxs.status2, AR_hw_upload_data));

	/* status3 */
	printf("    RX timestamp: %u\n", rxs.status3);
	last_ts = rxs.status3;

	/* status4 */
	printf("    GI: %d, 2040: %d, parallel40: %d, stbc=%d\n",
	    MF(rxs.status4, AR_gi),
	    MF(rxs.status4, AR_2040),
	    MF(rxs.status4, AR_parallel40),
	    MF(rxs.status4, AR_rx_stbc));
	printf("    Not sounding: %d, ness: %d, upload_valid: %d\n",
	    MF(rxs.status4, AR_rx_not_sounding),
	    MS(rxs.status4, AR_rx_ness),
	    MS(rxs.status4, AR_hw_upload_data_valid));
	printf("    RX antenna: 0x%08x\n",
	    MS(rxs.status4, AR_rx_antenna));

	/* EVM */
	/* status6 - 9 */
	printf("    EVM: 0x%08x; 0x%08x; 0x%08x; 0x%08x\n",
	    rxs.status6,
	    rxs.status7,
	    rxs.status8,
	    rxs.status9);

	/* status10 - ? */

	/* status11 */
	printf("    RX done: %d, RX frame ok: %d, CRC error: %d\n",
	    MF(rxs.status11, AR_rx_done),
	    MF(rxs.status11, AR_rx_frame_ok),
	    MF(rxs.status11, AR_crc_err));
	printf("    Decrypt CRC err: %d, PHY err: %d, MIC err: %d\n",
	    MF(rxs.status11, AR_decrypt_crc_err),
	    MF(rxs.status11, AR_phyerr),
	    MF(rxs.status11, AR_michael_err));
	printf("    Pre delim CRC err: %d, uAPSD Trig: %d\n",
	    MF(rxs.status11, AR_pre_delim_crc_err),
	    MF(rxs.status11, AR_apsd_trig));
	printf("    RXKeyIdxValid: %d, KeyIdx: %d, PHY error: %d\n",
	    MF(rxs.status11, AR_rx_key_idx_valid),
	    MS(rxs.status11, AR_key_idx),
	    MS(rxs.status11, AR_phy_err_code));
	printf("    RX more Aggr: %d, RX aggr %d, post delim CRC err: %d\n",
	    MF(rxs.status11, AR_rx_more_aggr),
	    MF(rxs.status11, AR_rx_aggr),
	    MF(rxs.status11, AR_post_delim_crc_err));
	printf("    hw upload data type: %d; position bit: %d\n",
	    MS(rxs.status11, AR_hw_upload_data_type),
	    MF(rxs.status11, AR_position_bit));
	printf("    Hi RX chain: %d, RxFirstAggr: %d, DecryptBusy: %d, KeyMiss: %d\n",
	    MF(rxs.status11, AR_hi_rx_chain),
	    MF(rxs.status11, AR_rx_first_aggr),
	    MF(rxs.status11, AR_decrypt_busy_err),
	    MF(rxs.status11, AR_key_miss));
}
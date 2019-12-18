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
typedef  int u64 ;
typedef  int u32 ;
struct sta_info {int acct_terminate_cause; int last_rx_bytes_lo; int last_tx_bytes_lo; int /*<<< orphan*/  addr; scalar_t__ last_tx_bytes_hi; scalar_t__ last_rx_bytes_hi; int /*<<< orphan*/  acct_session_start; } ;
struct radius_msg {int dummy; } ;
struct os_reltime {int sec; } ;
struct hostapd_data {int /*<<< orphan*/  radius; TYPE_2__* conf; } ;
struct hostap_sta_driver_data {int rx_packets; int tx_packets; int rx_bytes; int tx_bytes; scalar_t__ bytes_64bit; } ;
struct TYPE_4__ {TYPE_1__* radius; } ;
struct TYPE_3__ {int /*<<< orphan*/  acct_server; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  RADIUS_ACCT ; 
 int /*<<< orphan*/  RADIUS_ACCT_INTERIM ; 
 int /*<<< orphan*/  RADIUS_ACCT_STATUS_TYPE_INTERIM_UPDATE ; 
 int /*<<< orphan*/  RADIUS_ACCT_STATUS_TYPE_STOP ; 
 int RADIUS_ACCT_TERMINATE_CAUSE_ADMIN_REBOOT ; 
 int /*<<< orphan*/  RADIUS_ATTR_ACCT_INPUT_GIGAWORDS ; 
 int /*<<< orphan*/  RADIUS_ATTR_ACCT_INPUT_OCTETS ; 
 int /*<<< orphan*/  RADIUS_ATTR_ACCT_INPUT_PACKETS ; 
 int /*<<< orphan*/  RADIUS_ATTR_ACCT_OUTPUT_GIGAWORDS ; 
 int /*<<< orphan*/  RADIUS_ATTR_ACCT_OUTPUT_OCTETS ; 
 int /*<<< orphan*/  RADIUS_ATTR_ACCT_OUTPUT_PACKETS ; 
 int /*<<< orphan*/  RADIUS_ATTR_ACCT_SESSION_TIME ; 
 int /*<<< orphan*/  RADIUS_ATTR_ACCT_TERMINATE_CAUSE ; 
 struct radius_msg* accounting_msg (struct hostapd_data*,struct sta_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ accounting_sta_update_stats (struct hostapd_data*,struct sta_info*,struct hostap_sta_driver_data*) ; 
 scalar_t__ eloop_terminated () ; 
 int /*<<< orphan*/  os_get_reltime (struct os_reltime*) ; 
 int /*<<< orphan*/  os_reltime_sub (struct os_reltime*,int /*<<< orphan*/ *,struct os_reltime*) ; 
 scalar_t__ radius_client_send (int /*<<< orphan*/ ,struct radius_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radius_msg_add_attr_int32 (struct radius_msg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radius_msg_free (struct radius_msg*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void accounting_sta_report(struct hostapd_data *hapd,
				  struct sta_info *sta, int stop)
{
	struct radius_msg *msg;
	int cause = sta->acct_terminate_cause;
	struct hostap_sta_driver_data data;
	struct os_reltime now_r, diff;
	u64 bytes;

	if (!hapd->conf->radius->acct_server)
		return;

	msg = accounting_msg(hapd, sta,
			     stop ? RADIUS_ACCT_STATUS_TYPE_STOP :
			     RADIUS_ACCT_STATUS_TYPE_INTERIM_UPDATE);
	if (!msg) {
		wpa_printf(MSG_INFO, "Could not create RADIUS Accounting message");
		return;
	}

	os_get_reltime(&now_r);
	os_reltime_sub(&now_r, &sta->acct_session_start, &diff);
	if (!radius_msg_add_attr_int32(msg, RADIUS_ATTR_ACCT_SESSION_TIME,
				       diff.sec)) {
		wpa_printf(MSG_INFO, "Could not add Acct-Session-Time");
		goto fail;
	}

	if (accounting_sta_update_stats(hapd, sta, &data) == 0) {
		if (!radius_msg_add_attr_int32(msg,
					       RADIUS_ATTR_ACCT_INPUT_PACKETS,
					       data.rx_packets)) {
			wpa_printf(MSG_INFO, "Could not add Acct-Input-Packets");
			goto fail;
		}
		if (!radius_msg_add_attr_int32(msg,
					       RADIUS_ATTR_ACCT_OUTPUT_PACKETS,
					       data.tx_packets)) {
			wpa_printf(MSG_INFO, "Could not add Acct-Output-Packets");
			goto fail;
		}
		if (data.bytes_64bit)
			bytes = data.rx_bytes;
		else
			bytes = ((u64) sta->last_rx_bytes_hi << 32) |
				sta->last_rx_bytes_lo;
		if (!radius_msg_add_attr_int32(msg,
					       RADIUS_ATTR_ACCT_INPUT_OCTETS,
					       (u32) bytes)) {
			wpa_printf(MSG_INFO, "Could not add Acct-Input-Octets");
			goto fail;
		}
		if (!radius_msg_add_attr_int32(msg,
					       RADIUS_ATTR_ACCT_INPUT_GIGAWORDS,
					       (u32) (bytes >> 32))) {
			wpa_printf(MSG_INFO, "Could not add Acct-Input-Gigawords");
			goto fail;
		}
		if (data.bytes_64bit)
			bytes = data.tx_bytes;
		else
			bytes = ((u64) sta->last_tx_bytes_hi << 32) |
				sta->last_tx_bytes_lo;
		if (!radius_msg_add_attr_int32(msg,
					       RADIUS_ATTR_ACCT_OUTPUT_OCTETS,
					       (u32) bytes)) {
			wpa_printf(MSG_INFO, "Could not add Acct-Output-Octets");
			goto fail;
		}
		if (!radius_msg_add_attr_int32(msg,
					       RADIUS_ATTR_ACCT_OUTPUT_GIGAWORDS,
					       (u32) (bytes >> 32))) {
			wpa_printf(MSG_INFO, "Could not add Acct-Output-Gigawords");
			goto fail;
		}
	}

	if (eloop_terminated())
		cause = RADIUS_ACCT_TERMINATE_CAUSE_ADMIN_REBOOT;

	if (stop && cause &&
	    !radius_msg_add_attr_int32(msg, RADIUS_ATTR_ACCT_TERMINATE_CAUSE,
				       cause)) {
		wpa_printf(MSG_INFO, "Could not add Acct-Terminate-Cause");
		goto fail;
	}

	if (radius_client_send(hapd->radius, msg,
			       stop ? RADIUS_ACCT : RADIUS_ACCT_INTERIM,
			       sta->addr) < 0)
		goto fail;
	return;

 fail:
	radius_msg_free(msg);
}
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
typedef  int /*<<< orphan*/  const u8 ;
typedef  int u16 ;
struct eap_sm {int dummy; } ;
struct eap_gpsk_data {scalar_t__ state; int /*<<< orphan*/  specifier; int /*<<< orphan*/  vendor; int /*<<< orphan*/  sk_len; int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int EAP_GPSK_MAX_MIC_LEN ; 
 int /*<<< orphan*/  FAILURE ; 
 scalar_t__ GPSK_3 ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  SUCCESS ; 
 int WPA_GET_BE16 (int /*<<< orphan*/  const*) ; 
 scalar_t__ eap_gpsk_compute_mic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*) ; 
 size_t eap_gpsk_mic_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_gpsk_state (struct eap_gpsk_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ os_memcmp_const (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void eap_gpsk_process_gpsk_4(struct eap_sm *sm,
				    struct eap_gpsk_data *data,
				    const u8 *payload, size_t payloadlen)
{
	const u8 *pos, *end;
	u16 alen;
	size_t miclen;
	u8 mic[EAP_GPSK_MAX_MIC_LEN];

	if (data->state != GPSK_3)
		return;

	wpa_printf(MSG_DEBUG, "EAP-GPSK: Received Response/GPSK-4");

	pos = payload;
	end = payload + payloadlen;

	if (end - pos < 2) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Too short message for "
			   "PD_Payload_1 length");
		eap_gpsk_state(data, FAILURE);
		return;
	}
	alen = WPA_GET_BE16(pos);
	pos += 2;
	if (end - pos < alen) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Too short message for "
			   "PD_Payload_1");
		eap_gpsk_state(data, FAILURE);
		return;
	}
	wpa_hexdump(MSG_DEBUG, "EAP-GPSK: PD_Payload_1", pos, alen);
	pos += alen;

	miclen = eap_gpsk_mic_len(data->vendor, data->specifier);
	if (end - pos < (int) miclen) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Message too short for MIC "
			   "(left=%lu miclen=%lu)",
			   (unsigned long) (end - pos),
			   (unsigned long) miclen);
		eap_gpsk_state(data, FAILURE);
		return;
	}
	if (eap_gpsk_compute_mic(data->sk, data->sk_len, data->vendor,
				 data->specifier, payload, pos - payload, mic)
	    < 0) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Failed to compute MIC");
		eap_gpsk_state(data, FAILURE);
		return;
	}
	if (os_memcmp_const(mic, pos, miclen) != 0) {
		wpa_printf(MSG_INFO, "EAP-GPSK: Incorrect MIC in GPSK-4");
		wpa_hexdump(MSG_DEBUG, "EAP-GPSK: Received MIC", pos, miclen);
		wpa_hexdump(MSG_DEBUG, "EAP-GPSK: Computed MIC", mic, miclen);
		eap_gpsk_state(data, FAILURE);
		return;
	}
	pos += miclen;

	if (pos != end) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Ignored %lu bytes of extra "
			   "data in the end of GPSK-4",
			   (unsigned long) (end - pos));
	}

	eap_gpsk_state(data, SUCCESS);
}
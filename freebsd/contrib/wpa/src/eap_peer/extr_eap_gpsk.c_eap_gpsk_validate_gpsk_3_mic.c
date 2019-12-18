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
struct eap_gpsk_data {int /*<<< orphan*/  specifier; int /*<<< orphan*/  vendor; int /*<<< orphan*/  sk_len; int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int EAP_GPSK_MAX_MIC_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ eap_gpsk_compute_mic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*) ; 
 size_t eap_gpsk_mic_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ os_memcmp_const (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static const u8 * eap_gpsk_validate_gpsk_3_mic(struct eap_gpsk_data *data,
					       const u8 *payload,
					       const u8 *pos, const u8 *end)
{
	size_t miclen;
	u8 mic[EAP_GPSK_MAX_MIC_LEN];

	if (pos == NULL)
		return NULL;

	miclen = eap_gpsk_mic_len(data->vendor, data->specifier);
	if (end - pos < (int) miclen) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Message too short for MIC "
			   "(left=%lu miclen=%lu)",
			   (unsigned long) (end - pos),
			   (unsigned long) miclen);
		return NULL;
	}
	if (eap_gpsk_compute_mic(data->sk, data->sk_len, data->vendor,
				 data->specifier, payload, pos - payload, mic)
	    < 0) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Failed to compute MIC");
		return NULL;
	}
	if (os_memcmp_const(mic, pos, miclen) != 0) {
		wpa_printf(MSG_INFO, "EAP-GPSK: Incorrect MIC in GPSK-3");
		wpa_hexdump(MSG_DEBUG, "EAP-GPSK: Received MIC", pos, miclen);
		wpa_hexdump(MSG_DEBUG, "EAP-GPSK: Computed MIC", mic, miclen);
		return NULL;
	}
	pos += miclen;

	return pos;
}
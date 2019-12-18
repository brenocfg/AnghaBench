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
typedef  int /*<<< orphan*/  u8 ;
struct eap_gpsk_data {int /*<<< orphan*/  const* rand_server; int /*<<< orphan*/  const* rand_peer; } ;

/* Variables and functions */
 int EAP_GPSK_RAND_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static const u8 * eap_gpsk_validate_rand(struct eap_gpsk_data *data,
					 const u8 *pos, const u8 *end)
{
	if (end - pos < EAP_GPSK_RAND_LEN) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Message too short for "
			   "RAND_Peer");
		return NULL;
	}
	if (os_memcmp(pos, data->rand_peer, EAP_GPSK_RAND_LEN) != 0) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: RAND_Peer in GPSK-2 and "
			   "GPSK-3 did not match");
		wpa_hexdump(MSG_DEBUG, "EAP-GPSK: RAND_Peer in GPSK-2",
			    data->rand_peer, EAP_GPSK_RAND_LEN);
		wpa_hexdump(MSG_DEBUG, "EAP-GPSK: RAND_Peer in GPSK-3",
			    pos, EAP_GPSK_RAND_LEN);
		return NULL;
	}
	pos += EAP_GPSK_RAND_LEN;

	if (end - pos < EAP_GPSK_RAND_LEN) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Message too short for "
			   "RAND_Server");
		return NULL;
	}
	if (os_memcmp(pos, data->rand_server, EAP_GPSK_RAND_LEN) != 0) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: RAND_Server in GPSK-1 and "
			   "GPSK-3 did not match");
		wpa_hexdump(MSG_DEBUG, "EAP-GPSK: RAND_Server in GPSK-1",
			    data->rand_server, EAP_GPSK_RAND_LEN);
		wpa_hexdump(MSG_DEBUG, "EAP-GPSK: RAND_Server in GPSK-3",
			    pos, EAP_GPSK_RAND_LEN);
		return NULL;
	}
	pos += EAP_GPSK_RAND_LEN;

	return pos;
}
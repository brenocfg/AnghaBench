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
struct eap_gpsk_data {size_t id_server_len; int /*<<< orphan*/  const* id_server; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 size_t WPA_GET_BE16 (int /*<<< orphan*/  const*) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static const u8 * eap_gpsk_validate_id_server(struct eap_gpsk_data *data,
					      const u8 *pos, const u8 *end)
{
	size_t len;

	if (pos == NULL)
		return NULL;

	if (end - pos < (int) 2) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Message too short for "
			   "length(ID_Server)");
		return NULL;
	}

	len = WPA_GET_BE16(pos);
	pos += 2;

	if (end - pos < (int) len) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Message too short for "
			   "ID_Server");
		return NULL;
	}

	if (len != data->id_server_len ||
	    os_memcmp(pos, data->id_server, len) != 0) {
		wpa_printf(MSG_INFO, "EAP-GPSK: ID_Server did not match with "
			   "the one used in GPSK-1");
		wpa_hexdump_ascii(MSG_DEBUG, "EAP-GPSK: ID_Server in GPSK-1",
				  data->id_server, data->id_server_len);
		wpa_hexdump_ascii(MSG_DEBUG, "EAP-GPSK: ID_Server in GPSK-3",
				  pos, len);
		return NULL;
	}

	pos += len;

	return pos;
}
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
typedef  int u16 ;
struct eap_gpsk_data {int id_server_len; int /*<<< orphan*/ * id_server; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int WPA_GET_BE16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_memdup (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static const u8 * eap_gpsk_process_id_server(struct eap_gpsk_data *data,
					     const u8 *pos, const u8 *end)
{
	u16 alen;

	if (end - pos < 2) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Too short GPSK-1 packet");
		return NULL;
	}
	alen = WPA_GET_BE16(pos);
	pos += 2;
	if (end - pos < alen) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: ID_Server overflow");
		return NULL;
	}
	os_free(data->id_server);
	data->id_server = os_memdup(pos, alen);
	if (data->id_server == NULL) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: No memory for ID_Server");
		return NULL;
	}
	data->id_server_len = alen;
	wpa_hexdump_ascii(MSG_DEBUG, "EAP-GPSK: ID_Server",
			  data->id_server, data->id_server_len);
	pos += alen;

	return pos;
}
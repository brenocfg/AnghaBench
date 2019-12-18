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
typedef  int /*<<< orphan*/  u8 ;
struct eap_fast_data {TYPE_1__* current_pac; int /*<<< orphan*/  pac; } ;
struct TYPE_2__ {int /*<<< orphan*/  a_id_info_len; int /*<<< orphan*/  a_id_info; int /*<<< orphan*/  pac_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  PAC_TYPE_MACHINE_AUTHENTICATION ; 
 int /*<<< orphan*/  PAC_TYPE_TUNNEL_PAC ; 
 void* eap_fast_get_pac (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eap_fast_select_pac(struct eap_fast_data *data,
				const u8 *a_id, size_t a_id_len)
{
	data->current_pac = eap_fast_get_pac(data->pac, a_id, a_id_len,
					     PAC_TYPE_TUNNEL_PAC);
	if (data->current_pac == NULL) {
		/*
		 * Tunnel PAC was not available for this A-ID. Try to use
		 * Machine Authentication PAC, if one is available.
		 */
		data->current_pac = eap_fast_get_pac(
			data->pac, a_id, a_id_len,
			PAC_TYPE_MACHINE_AUTHENTICATION);
	}

	if (data->current_pac) {
		wpa_printf(MSG_DEBUG, "EAP-FAST: PAC found for this A-ID "
			   "(PAC-Type %d)", data->current_pac->pac_type);
		wpa_hexdump_ascii(MSG_MSGDUMP, "EAP-FAST: A-ID-Info",
				  data->current_pac->a_id_info,
				  data->current_pac->a_id_info_len);
	}
}
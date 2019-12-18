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
struct eap_gpsk_data {int /*<<< orphan*/  rand_server; } ;

/* Variables and functions */
 int EAP_GPSK_RAND_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static const u8 * eap_gpsk_process_rand_server(struct eap_gpsk_data *data,
					       const u8 *pos, const u8 *end)
{
	if (pos == NULL)
		return NULL;

	if (end - pos < EAP_GPSK_RAND_LEN) {
		wpa_printf(MSG_DEBUG, "EAP-GPSK: RAND_Server overflow");
		return NULL;
	}
	os_memcpy(data->rand_server, pos, EAP_GPSK_RAND_LEN);
	wpa_hexdump(MSG_DEBUG, "EAP-GPSK: RAND_Server",
		    data->rand_server, EAP_GPSK_RAND_LEN);
	pos += EAP_GPSK_RAND_LEN;

	return pos;
}
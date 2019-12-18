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
struct TYPE_2__ {int /*<<< orphan*/  conn; } ;
struct eap_teap_data {int id_len; int /*<<< orphan*/ * session_id; TYPE_1__ ssl; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_TYPE_TEAP ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (size_t const) ; 
 int tls_get_tls_unique (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t const) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int eap_teap_session_id(struct eap_teap_data *data)
{
	const size_t max_id_len = 100;
	int res;

	os_free(data->session_id);
	data->session_id = os_malloc(max_id_len);
	if (!data->session_id)
		return -1;

	data->session_id[0] = EAP_TYPE_TEAP;
	res = tls_get_tls_unique(data->ssl.conn, data->session_id + 1,
				 max_id_len - 1);
	if (res < 0) {
		os_free(data->session_id);
		data->session_id = NULL;
		wpa_printf(MSG_ERROR, "EAP-TEAP: Failed to derive Session-Id");
		return -1;
	}

	data->id_len = 1 + res;
	wpa_hexdump(MSG_DEBUG, "EAP-TEAP: Derived Session-Id",
		    data->session_id, data->id_len);
	return 0;
}
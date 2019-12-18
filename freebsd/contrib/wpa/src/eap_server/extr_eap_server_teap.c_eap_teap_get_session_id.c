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
struct TYPE_2__ {int /*<<< orphan*/  conn; } ;
struct eap_teap_data {scalar_t__ state; TYPE_1__ ssl; } ;
struct eap_sm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_TYPE_TEAP ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (size_t const) ; 
 int tls_get_tls_unique (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t const) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static u8 * eap_teap_get_session_id(struct eap_sm *sm, void *priv, size_t *len)
{
	struct eap_teap_data *data = priv;
	const size_t max_id_len = 100;
	int res;
	u8 *id;

	if (data->state != SUCCESS)
		return NULL;

	id = os_malloc(max_id_len);
	if (!id)
		return NULL;

	id[0] = EAP_TYPE_TEAP;
	res = tls_get_tls_unique(data->ssl.conn, id + 1, max_id_len - 1);
	if (res < 0) {
		os_free(id);
		wpa_printf(MSG_ERROR, "EAP-TEAP: Failed to derive Session-Id");
		return NULL;
	}

	*len = 1 + res;
	wpa_hexdump(MSG_DEBUG, "EAP-TEAP: Derived Session-Id", id, *len);
	return id;
}
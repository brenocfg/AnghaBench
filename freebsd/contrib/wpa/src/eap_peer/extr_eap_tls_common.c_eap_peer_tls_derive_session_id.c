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
typedef  scalar_t__ u8 ;
struct tls_random {scalar_t__* client_random; scalar_t__* server_random; int client_random_len; int server_random_len; } ;
struct eap_ssl_data {int /*<<< orphan*/  conn; scalar_t__ tls_v13; } ;
struct eap_sm {int /*<<< orphan*/  ssl_ctx; } ;

/* Variables and functions */
 scalar_t__ EAP_TYPE_TLS ; 
 scalar_t__* eap_peer_tls_derive_key (struct eap_sm*,struct eap_ssl_data*,char*,scalar_t__ const*,int,int) ; 
 int /*<<< orphan*/  os_free (scalar_t__*) ; 
 scalar_t__* os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (scalar_t__*,scalar_t__*,int) ; 
 scalar_t__ tls_connection_get_random (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tls_random*) ; 

u8 * eap_peer_tls_derive_session_id(struct eap_sm *sm,
				    struct eap_ssl_data *data, u8 eap_type,
				    size_t *len)
{
	struct tls_random keys;
	u8 *out;

	if (eap_type == EAP_TYPE_TLS && data->tls_v13) {
		u8 *id, *method_id;
		const u8 context[] = { EAP_TYPE_TLS };

		/* Session-Id = <EAP-Type> || Method-Id
		 * Method-Id = TLS-Exporter("EXPORTER_EAP_TLS_Method-Id",
		 *                          Type-Code, 64)
		 */
		*len = 1 + 64;
		id = os_malloc(*len);
		if (!id)
			return NULL;
		method_id = eap_peer_tls_derive_key(
			sm, data, "EXPORTER_EAP_TLS_Method-Id", context, 1, 64);
		if (!method_id) {
			os_free(id);
			return NULL;
		}
		id[0] = eap_type;
		os_memcpy(id + 1, method_id, 64);
		os_free(method_id);
		return id;
	}

	if (tls_connection_get_random(sm->ssl_ctx, data->conn, &keys) ||
	    keys.client_random == NULL || keys.server_random == NULL)
		return NULL;

	*len = 1 + keys.client_random_len + keys.server_random_len;
	out = os_malloc(*len);
	if (out == NULL)
		return NULL;

	/* Session-Id = EAP type || client.random || server.random */
	out[0] = eap_type;
	os_memcpy(out + 1, keys.client_random, keys.client_random_len);
	os_memcpy(out + 1 + keys.client_random_len, keys.server_random,
		  keys.server_random_len);

	return out;
}
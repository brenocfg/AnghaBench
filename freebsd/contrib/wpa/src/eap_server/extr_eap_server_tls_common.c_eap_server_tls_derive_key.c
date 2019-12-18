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
struct eap_ssl_data {int /*<<< orphan*/  conn; } ;
struct eap_sm {int /*<<< orphan*/  ssl_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 scalar_t__ tls_connection_export_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,size_t) ; 

u8 * eap_server_tls_derive_key(struct eap_sm *sm, struct eap_ssl_data *data,
			       const char *label, const u8 *context,
			       size_t context_len, size_t len)
{
	u8 *out;

	out = os_malloc(len);
	if (out == NULL)
		return NULL;

	if (tls_connection_export_key(sm->ssl_ctx, data->conn, label,
				      context, context_len, out, len)) {
		os_free(out);
		return NULL;
	}

	return out;
}
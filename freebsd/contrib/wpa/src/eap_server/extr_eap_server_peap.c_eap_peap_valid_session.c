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
typedef  int u8 ;
struct wpabuf {int dummy; } ;
struct eap_sm {int identity_len; int /*<<< orphan*/  identity; int /*<<< orphan*/  ssl_ctx; int /*<<< orphan*/  tls_session_lifetime; } ;
struct TYPE_2__ {int /*<<< orphan*/  conn; } ;
struct eap_peap_data {TYPE_1__ ssl; } ;

/* Variables and functions */
 int EAP_TYPE_PEAP ; 
 scalar_t__ tls_connection_resumed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_connection_set_success_data (int /*<<< orphan*/ ,struct wpabuf*) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int) ; 

__attribute__((used)) static void eap_peap_valid_session(struct eap_sm *sm,
				   struct eap_peap_data *data)
{
	struct wpabuf *buf;

	if (!sm->tls_session_lifetime ||
	    tls_connection_resumed(sm->ssl_ctx, data->ssl.conn))
		return;

	buf = wpabuf_alloc(1 + 1 + sm->identity_len);
	if (!buf)
		return;
	wpabuf_put_u8(buf, EAP_TYPE_PEAP);
	if (sm->identity) {
		u8 id_len;

		if (sm->identity_len <= 255)
			id_len = sm->identity_len;
		else
			id_len = 255;
		wpabuf_put_u8(buf, id_len);
		wpabuf_put_data(buf, sm->identity, id_len);
	} else {
		wpabuf_put_u8(buf, 0);
	}
	tls_connection_set_success_data(data->ssl.conn, buf);
}
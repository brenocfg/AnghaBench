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
struct wpabuf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  conn; } ;
struct eap_tls_data {TYPE_1__ ssl; int /*<<< orphan*/  eap_type; } ;
struct eap_sm {int /*<<< orphan*/  tls_session_lifetime; } ;

/* Variables and functions */
 int /*<<< orphan*/  tls_connection_set_success_data (int /*<<< orphan*/ ,struct wpabuf*) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eap_tls_valid_session(struct eap_sm *sm, struct eap_tls_data *data)
{
	struct wpabuf *buf;

	if (!sm->tls_session_lifetime)
		return;

	buf = wpabuf_alloc(1);
	if (!buf)
		return;
	wpabuf_put_u8(buf, data->eap_type);
	tls_connection_set_success_data(data->ssl.conn, buf);
}
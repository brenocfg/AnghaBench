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
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_CODE_REQUEST ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 struct wpabuf* eap_tls_msg_alloc (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int) ; 

struct wpabuf * eap_server_tls_build_ack(u8 id, int eap_type, int version)
{
	struct wpabuf *req;

	req = eap_tls_msg_alloc(eap_type, 1, EAP_CODE_REQUEST, id);
	if (req == NULL)
		return NULL;
	wpa_printf(MSG_DEBUG, "SSL: Building ACK");
	wpabuf_put_u8(req, version); /* Flags */
	return req;
}
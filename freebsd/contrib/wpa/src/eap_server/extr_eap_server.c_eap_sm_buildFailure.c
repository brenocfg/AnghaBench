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
struct eap_sm {int dummy; } ;
struct eap_hdr {int /*<<< orphan*/  length; int /*<<< orphan*/  identifier; int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_CODE_FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  host_to_be16 (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 struct eap_hdr* wpabuf_put (struct wpabuf*,int) ; 

__attribute__((used)) static struct wpabuf * eap_sm_buildFailure(struct eap_sm *sm, u8 id)
{
	struct wpabuf *msg;
	struct eap_hdr *resp;
	wpa_printf(MSG_DEBUG, "EAP: Building EAP-Failure (id=%d)", id);

	msg = wpabuf_alloc(sizeof(*resp));
	if (msg == NULL)
		return NULL;
	resp = wpabuf_put(msg, sizeof(*resp));
	resp->code = EAP_CODE_FAILURE;
	resp->identifier = id;
	resp->length = host_to_be16(sizeof(*resp));

	return msg;
}
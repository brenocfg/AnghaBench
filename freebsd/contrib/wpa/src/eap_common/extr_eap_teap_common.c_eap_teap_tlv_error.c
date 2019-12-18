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
struct wpabuf {int dummy; } ;
typedef  enum teap_error_codes { ____Placeholder_teap_error_codes } teap_error_codes ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int TEAP_TLV_ERROR ; 
 int TEAP_TLV_MANDATORY ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_be32 (struct wpabuf*,int) ; 

struct wpabuf * eap_teap_tlv_error(enum teap_error_codes error)
{
	struct wpabuf *buf;

	buf = wpabuf_alloc(4 + 4);
	if (!buf)
		return NULL;
	wpa_printf(MSG_DEBUG, "EAP-TEAP: Add Error TLV(Error Code=%d)",
		   error);
	wpabuf_put_be16(buf, TEAP_TLV_MANDATORY | TEAP_TLV_ERROR);
	wpabuf_put_be16(buf, 4);
	wpabuf_put_be32(buf, error);
	return buf;
}
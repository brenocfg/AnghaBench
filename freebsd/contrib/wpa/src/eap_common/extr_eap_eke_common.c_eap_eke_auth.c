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
struct eap_eke_session {int /*<<< orphan*/  auth_len; int /*<<< orphan*/  ka; int /*<<< orphan*/  prf; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int eap_eke_prf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_strlen (char const*) ; 
 int /*<<< orphan*/  wpa_hexdump_buf (int /*<<< orphan*/ ,char*,struct wpabuf const*) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf const*) ; 

int eap_eke_auth(struct eap_eke_session *sess, const char *label,
		 const struct wpabuf *msgs, u8 *auth)
{
	wpa_printf(MSG_DEBUG, "EAP-EKE: Auth(%s)", label);
	wpa_hexdump_key(MSG_DEBUG, "EAP-EKE: Ka for Auth",
			sess->ka, sess->auth_len);
	wpa_hexdump_buf(MSG_MSGDUMP, "EAP-EKE: Messages for Auth", msgs);
	return eap_eke_prf(sess->prf, sess->ka, sess->auth_len,
			   (const u8 *) label, os_strlen(label),
			   wpabuf_head(msgs), wpabuf_len(msgs), auth);
}
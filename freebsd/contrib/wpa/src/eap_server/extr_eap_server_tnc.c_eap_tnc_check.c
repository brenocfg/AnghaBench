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
typedef  int u8 ;
struct wpabuf {int dummy; } ;
struct eap_tnc_data {scalar_t__ state; } ;
struct eap_sm {int dummy; } ;
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 int const EAP_TNC_FLAGS_START ; 
 int const EAP_TNC_VERSION ; 
 int const EAP_TNC_VERSION_MASK ; 
 int /*<<< orphan*/  EAP_TYPE_TNC ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WAIT_FRAG_ACK ; 
 int* eap_hdr_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpabuf*,size_t*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static Boolean eap_tnc_check(struct eap_sm *sm, void *priv,
			     struct wpabuf *respData)
{
	struct eap_tnc_data *data = priv;
	const u8 *pos;
	size_t len;

	pos = eap_hdr_validate(EAP_VENDOR_IETF, EAP_TYPE_TNC, respData,
			       &len);
	if (pos == NULL) {
		wpa_printf(MSG_INFO, "EAP-TNC: Invalid frame");
		return TRUE;
	}

	if (len == 0 && data->state != WAIT_FRAG_ACK) {
		wpa_printf(MSG_INFO, "EAP-TNC: Invalid frame (empty)");
		return TRUE;
	}

	if (len == 0)
		return FALSE; /* Fragment ACK does not include flags */

	if ((*pos & EAP_TNC_VERSION_MASK) != EAP_TNC_VERSION) {
		wpa_printf(MSG_DEBUG, "EAP-TNC: Unsupported version %d",
			   *pos & EAP_TNC_VERSION_MASK);
		return TRUE;
	}

	if (*pos & EAP_TNC_FLAGS_START) {
		wpa_printf(MSG_DEBUG, "EAP-TNC: Peer used Start flag");
		return TRUE;
	}

	return FALSE;
}
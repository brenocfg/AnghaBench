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
struct eap_sm {scalar_t__ workaround; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static int eap_success_workaround(struct eap_sm *sm, int reqId, int lastId)
{
	/*
	 * At least Microsoft IAS and Meetinghouse Aegis seem to be sending
	 * EAP-Success/Failure with lastId + 1 even though RFC 3748 and
	 * RFC 4137 require that reqId == lastId. In addition, it looks like
	 * Ringmaster v2.1.2.0 would be using lastId + 2 in EAP-Success.
	 *
	 * Accept this kind of Id if EAP workarounds are enabled. These are
	 * unauthenticated plaintext messages, so this should have minimal
	 * security implications (bit easier to fake EAP-Success/Failure).
	 */
	if (sm->workaround && (reqId == ((lastId + 1) & 0xff) ||
			       reqId == ((lastId + 2) & 0xff))) {
		wpa_printf(MSG_DEBUG, "EAP: Workaround for unexpected "
			   "identifier field in EAP Success: "
			   "reqId=%d lastId=%d (these are supposed to be "
			   "same)", reqId, lastId);
		return 1;
	}
	wpa_printf(MSG_DEBUG, "EAP: EAP-Success Id mismatch - reqId=%d "
		   "lastId=%d", reqId, lastId);
	return 0;
}
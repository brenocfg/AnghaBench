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
struct eapol_sm {int /*<<< orphan*/  eap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  const* eap_get_eapSessionId (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  eap_key_available (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

const u8 * eapol_sm_get_session_id(struct eapol_sm *sm, size_t *len)
{
	if (sm == NULL || !eap_key_available(sm->eap)) {
		wpa_printf(MSG_DEBUG, "EAPOL: EAP Session-Id not available");
		return NULL;
	}
	return eap_get_eapSessionId(sm->eap, len);
}
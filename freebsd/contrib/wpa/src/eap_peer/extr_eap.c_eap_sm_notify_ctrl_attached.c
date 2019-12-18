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
struct eap_sm {int dummy; } ;
struct eap_peer_config {scalar_t__ pending_req_passphrase; scalar_t__ pending_req_pin; scalar_t__ pending_req_otp; scalar_t__ pending_req_new_password; scalar_t__ pending_req_password; scalar_t__ pending_req_identity; } ;

/* Variables and functions */
 struct eap_peer_config* eap_get_config (struct eap_sm*) ; 
 int /*<<< orphan*/  eap_sm_request_identity (struct eap_sm*) ; 
 int /*<<< orphan*/  eap_sm_request_new_password (struct eap_sm*) ; 
 int /*<<< orphan*/  eap_sm_request_otp (struct eap_sm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_sm_request_passphrase (struct eap_sm*) ; 
 int /*<<< orphan*/  eap_sm_request_password (struct eap_sm*) ; 
 int /*<<< orphan*/  eap_sm_request_pin (struct eap_sm*) ; 

void eap_sm_notify_ctrl_attached(struct eap_sm *sm)
{
	struct eap_peer_config *config = eap_get_config(sm);

	if (config == NULL)
		return;

	/* Re-send any pending requests for user data since a new control
	 * interface was added. This handles cases where the EAP authentication
	 * starts immediately after system startup when the user interface is
	 * not yet running. */
	if (config->pending_req_identity)
		eap_sm_request_identity(sm);
	if (config->pending_req_password)
		eap_sm_request_password(sm);
	if (config->pending_req_new_password)
		eap_sm_request_new_password(sm);
	if (config->pending_req_otp)
		eap_sm_request_otp(sm, NULL, 0);
	if (config->pending_req_pin)
		eap_sm_request_pin(sm);
	if (config->pending_req_passphrase)
		eap_sm_request_passphrase(sm);
}
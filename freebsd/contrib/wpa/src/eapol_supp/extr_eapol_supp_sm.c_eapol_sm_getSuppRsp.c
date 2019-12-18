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
struct eapol_sm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void eapol_sm_getSuppRsp(struct eapol_sm *sm)
{
	wpa_printf(MSG_DEBUG, "EAPOL: getSuppRsp");
	/* EAP layer processing; no special code is needed, since Supplicant
	 * Backend state machine is waiting for eapNoResp or eapResp to be set
	 * and these are only set in the EAP state machine when the processing
	 * has finished. */
}
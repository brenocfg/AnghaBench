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
typedef  int /*<<< orphan*/  EapType ;
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  eap_allowed_method (struct eap_sm*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ eap_peer_get_eap_method (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Boolean eap_sm_allowMethod(struct eap_sm *sm, int vendor,
				  EapType method)
{
	if (!eap_allowed_method(sm, vendor, method)) {
		wpa_printf(MSG_DEBUG, "EAP: configuration does not allow: "
			   "vendor %u method %u", vendor, method);
		return FALSE;
	}
	if (eap_peer_get_eap_method(vendor, method))
		return TRUE;
	wpa_printf(MSG_DEBUG, "EAP: not included in build: "
		   "vendor %u method %u", vendor, method);
	return FALSE;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct eap_sm {int user_eap_method_index; int currentId; TYPE_2__* user; int /*<<< orphan*/  update_user; int /*<<< orphan*/ * identity; } ;
struct TYPE_4__ {TYPE_1__* methods; } ;
struct TYPE_3__ {int vendor; scalar_t__ method; } ;
typedef  scalar_t__ EapType ;

/* Variables and functions */
 int EAP_MAX_METHODS ; 
 scalar_t__ EAP_TYPE_IDENTITY ; 
 scalar_t__ EAP_TYPE_NONE ; 
 int EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,scalar_t__) ; 

__attribute__((used)) static EapType eap_sm_Policy_getNextMethod(struct eap_sm *sm, int *vendor)
{
	EapType next;
	int idx = sm->user_eap_method_index;

	/* In theory, there should be no problems with starting
	 * re-authentication with something else than EAP-Request/Identity and
	 * this does indeed work with wpa_supplicant. However, at least Funk
	 * Supplicant seemed to ignore re-auth if it skipped
	 * EAP-Request/Identity.
	 * Re-auth sets currentId == -1, so that can be used here to select
	 * whether Identity needs to be requested again. */
	if (sm->identity == NULL || sm->currentId == -1) {
		*vendor = EAP_VENDOR_IETF;
		next = EAP_TYPE_IDENTITY;
		sm->update_user = TRUE;
	} else if (sm->user && idx < EAP_MAX_METHODS &&
		   (sm->user->methods[idx].vendor != EAP_VENDOR_IETF ||
		    sm->user->methods[idx].method != EAP_TYPE_NONE)) {
		*vendor = sm->user->methods[idx].vendor;
		next = sm->user->methods[idx].method;
		sm->user_eap_method_index++;
	} else {
		*vendor = EAP_VENDOR_IETF;
		next = EAP_TYPE_NONE;
	}
	wpa_printf(MSG_DEBUG, "EAP: getNextMethod: vendor %d type %d",
		   *vendor, next);
	return next;
}
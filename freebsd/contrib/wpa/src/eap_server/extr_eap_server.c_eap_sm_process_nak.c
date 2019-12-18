#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct eap_sm {int user_eap_method_index; TYPE_1__* user; } ;
struct TYPE_5__ {scalar_t__ vendor; scalar_t__ method; } ;
struct TYPE_4__ {TYPE_2__* methods; } ;

/* Variables and functions */
 int EAP_MAX_METHODS ; 
 scalar_t__ EAP_TYPE_NONE ; 
 scalar_t__ EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  os_memmove (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

void eap_sm_process_nak(struct eap_sm *sm, const u8 *nak_list, size_t len)
{
	int i;
	size_t j;

	if (sm->user == NULL)
		return;

	wpa_printf(MSG_MSGDUMP, "EAP: processing NAK (current EAP method "
		   "index %d)", sm->user_eap_method_index);

	wpa_hexdump(MSG_MSGDUMP, "EAP: configured methods",
		    (u8 *) sm->user->methods,
		    EAP_MAX_METHODS * sizeof(sm->user->methods[0]));
	wpa_hexdump(MSG_MSGDUMP, "EAP: list of methods supported by the peer",
		    nak_list, len);

	i = sm->user_eap_method_index;
	while (i < EAP_MAX_METHODS &&
	       (sm->user->methods[i].vendor != EAP_VENDOR_IETF ||
		sm->user->methods[i].method != EAP_TYPE_NONE)) {
		if (sm->user->methods[i].vendor != EAP_VENDOR_IETF)
			goto not_found;
		for (j = 0; j < len; j++) {
			if (nak_list[j] == sm->user->methods[i].method) {
				break;
			}
		}

		if (j < len) {
			/* found */
			i++;
			continue;
		}

	not_found:
		/* not found - remove from the list */
		if (i + 1 < EAP_MAX_METHODS) {
			os_memmove(&sm->user->methods[i],
				   &sm->user->methods[i + 1],
				   (EAP_MAX_METHODS - i - 1) *
				   sizeof(sm->user->methods[0]));
		}
		sm->user->methods[EAP_MAX_METHODS - 1].vendor =
			EAP_VENDOR_IETF;
		sm->user->methods[EAP_MAX_METHODS - 1].method = EAP_TYPE_NONE;
	}

	wpa_hexdump(MSG_MSGDUMP, "EAP: new list of configured methods",
		    (u8 *) sm->user->methods, EAP_MAX_METHODS *
		    sizeof(sm->user->methods[0]));
}
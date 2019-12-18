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
struct eapol_sm {scalar_t__ SUPP_PAE_state; scalar_t__ suppPortStatus; int /*<<< orphan*/  eap; } ;

/* Variables and functions */
 scalar_t__ Authorized ; 
 scalar_t__ SUPP_PAE_AUTHENTICATED ; 
 char const* eap_sm_get_method_name (int /*<<< orphan*/ ) ; 

const char * eapol_sm_get_method_name(struct eapol_sm *sm)
{
	if (sm->SUPP_PAE_state != SUPP_PAE_AUTHENTICATED ||
	    sm->suppPortStatus != Authorized)
		return NULL;

	return eap_sm_get_method_name(sm->eap);
}
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
struct eapol_sm {scalar_t__ SUPP_PAE_state; } ;

/* Variables and functions */
 scalar_t__ SUPP_PAE_AUTHENTICATED ; 
 int /*<<< orphan*/  eapol_sm_txStart (struct eapol_sm*) ; 

void eapol_sm_request_reauth(struct eapol_sm *sm)
{
	if (sm == NULL || sm->SUPP_PAE_state != SUPP_PAE_AUTHENTICATED)
		return;
	eapol_sm_txStart(sm);
}
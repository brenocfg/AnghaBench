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
struct eapol_sm {int /*<<< orphan*/  eap; } ;

/* Variables and functions */
 int /*<<< orphan*/  eap_notify_lower_layer_success (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eapol_sm_step (struct eapol_sm*) ; 

void eapol_sm_notify_lower_layer_success(struct eapol_sm *sm, int in_eapol_sm)
{
	if (sm == NULL)
		return;
	eap_notify_lower_layer_success(sm->eap);
	if (!in_eapol_sm)
		eapol_sm_step(sm);
}
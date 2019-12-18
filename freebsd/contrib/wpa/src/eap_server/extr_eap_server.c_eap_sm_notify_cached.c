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
struct eap_sm {int /*<<< orphan*/  EAP_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_SUCCESS ; 

void eap_sm_notify_cached(struct eap_sm *sm)
{
	if (sm == NULL)
		return;

	sm->EAP_state = EAP_SUCCESS;
}
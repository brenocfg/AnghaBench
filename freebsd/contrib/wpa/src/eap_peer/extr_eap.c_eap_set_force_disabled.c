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
struct eap_sm {int force_disabled; } ;

/* Variables and functions */

void eap_set_force_disabled(struct eap_sm *sm, int disabled)
{
	sm->force_disabled = disabled;
}
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
struct wpabuf {int dummy; } ;
struct eapol_state_machine {struct wpabuf* radius_cui; } ;

/* Variables and functions */

struct wpabuf * ieee802_1x_get_radius_cui(struct eapol_state_machine *sm)
{
	if (sm == NULL)
		return NULL;
	return sm->radius_cui;
}
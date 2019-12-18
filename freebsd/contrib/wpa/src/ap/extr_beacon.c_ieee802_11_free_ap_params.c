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
struct wpa_driver_ap_params {int /*<<< orphan*/ * proberesp; int /*<<< orphan*/ * head; int /*<<< orphan*/ * tail; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 

void ieee802_11_free_ap_params(struct wpa_driver_ap_params *params)
{
	os_free(params->tail);
	params->tail = NULL;
	os_free(params->head);
	params->head = NULL;
	os_free(params->proberesp);
	params->proberesp = NULL;
}
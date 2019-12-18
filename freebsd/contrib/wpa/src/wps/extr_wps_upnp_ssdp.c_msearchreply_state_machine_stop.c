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
struct advertisement_state_machine {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  dl_list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct advertisement_state_machine*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

void msearchreply_state_machine_stop(struct advertisement_state_machine *a)
{
	wpa_printf(MSG_DEBUG, "WPS UPnP: M-SEARCH stop");
	dl_list_del(&a->list);
	os_free(a);
}
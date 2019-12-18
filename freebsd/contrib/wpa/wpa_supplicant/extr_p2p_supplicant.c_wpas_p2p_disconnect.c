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
struct wpa_supplicant {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  P2P_GROUP_REMOVAL_REQUESTED ; 
 scalar_t__ wpas_p2p_group_delete (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 

int wpas_p2p_disconnect(struct wpa_supplicant *wpa_s)
{

	if (wpa_s == NULL)
		return -1;

	return wpas_p2p_group_delete(wpa_s, P2P_GROUP_REMOVAL_REQUESTED) < 0 ?
		-1 : 0;
}
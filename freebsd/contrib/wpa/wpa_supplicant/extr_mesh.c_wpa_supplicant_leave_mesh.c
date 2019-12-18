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
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int wpa_drv_leave_mesh (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_drv_set_operstate (struct wpa_supplicant*,int) ; 
 int /*<<< orphan*/  wpa_msg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpa_supplicant_mesh_deinit (struct wpa_supplicant*) ; 

int wpa_supplicant_leave_mesh(struct wpa_supplicant *wpa_s)
{
	int ret = 0;

	wpa_msg(wpa_s, MSG_INFO, "leaving mesh");

	/* Need to send peering close messages first */
	wpa_supplicant_mesh_deinit(wpa_s);

	ret = wpa_drv_leave_mesh(wpa_s);
	if (ret)
		wpa_msg(wpa_s, MSG_ERROR, "mesh leave error=%d", ret);

	wpa_drv_set_operstate(wpa_s, 1);

	return ret;
}
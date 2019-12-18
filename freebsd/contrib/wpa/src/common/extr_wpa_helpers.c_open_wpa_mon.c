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
struct wpa_ctrl {int dummy; } ;

/* Variables and functions */
 scalar_t__ wpa_ctrl_attach (struct wpa_ctrl*) ; 
 int /*<<< orphan*/  wpa_ctrl_close (struct wpa_ctrl*) ; 
 struct wpa_ctrl* wpa_open_ctrl (char const*) ; 

struct wpa_ctrl * open_wpa_mon(const char *ifname)
{
	struct wpa_ctrl *ctrl;

	ctrl = wpa_open_ctrl(ifname);
	if (ctrl == NULL)
		return NULL;
	if (wpa_ctrl_attach(ctrl) < 0) {
		wpa_ctrl_close(ctrl);
		return NULL;
	}

	return ctrl;
}
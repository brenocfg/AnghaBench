#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wpa_supplicant {TYPE_1__* p2pdev; } ;
struct TYPE_4__ {scalar_t__ update_config; } ;
struct TYPE_3__ {TYPE_2__* conf; int /*<<< orphan*/  confname; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ wpa_config_write (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void p2p_config_write(struct wpa_supplicant *wpa_s)
{
#ifndef CONFIG_NO_CONFIG_WRITE
	if (wpa_s->p2pdev->conf->update_config &&
	    wpa_config_write(wpa_s->p2pdev->confname, wpa_s->p2pdev->conf))
		wpa_printf(MSG_DEBUG, "P2P: Failed to update configuration");
#endif /* CONFIG_NO_CONFIG_WRITE */
}
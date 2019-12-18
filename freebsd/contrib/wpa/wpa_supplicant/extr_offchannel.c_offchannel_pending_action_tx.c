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
struct wpa_supplicant {void const* pending_action_tx; } ;

/* Variables and functions */

const void * offchannel_pending_action_tx(struct wpa_supplicant *wpa_s)
{
	return wpa_s->pending_action_tx;
}
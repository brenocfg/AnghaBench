#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wpa_supplicant {scalar_t__ bgscan_priv; TYPE_1__* bgscan; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* notify_beacon_loss ) (scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

void bgscan_notify_beacon_loss(struct wpa_supplicant *wpa_s)
{
	if (wpa_s->bgscan && wpa_s->bgscan_priv)
		wpa_s->bgscan->notify_beacon_loss(wpa_s->bgscan_priv);
}
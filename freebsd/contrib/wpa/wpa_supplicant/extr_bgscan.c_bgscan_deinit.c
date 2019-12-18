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
struct wpa_supplicant {int /*<<< orphan*/ * bgscan_priv; TYPE_1__* bgscan; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* deinit ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void bgscan_deinit(struct wpa_supplicant *wpa_s)
{
	if (wpa_s->bgscan && wpa_s->bgscan_priv) {
		wpa_printf(MSG_DEBUG, "bgscan: Deinitializing module '%s'",
			   wpa_s->bgscan->name);
		wpa_s->bgscan->deinit(wpa_s->bgscan_priv);
		wpa_s->bgscan = NULL;
		wpa_s->bgscan_priv = NULL;
	}
}
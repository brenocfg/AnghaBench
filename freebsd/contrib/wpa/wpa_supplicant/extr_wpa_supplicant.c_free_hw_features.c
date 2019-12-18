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
struct TYPE_3__ {int num_modes; TYPE_2__* modes; } ;
struct wpa_supplicant {TYPE_1__ hw; } ;
struct TYPE_4__ {struct TYPE_4__* rates; struct TYPE_4__* channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (TYPE_2__*) ; 

void free_hw_features(struct wpa_supplicant *wpa_s)
{
	int i;
	if (wpa_s->hw.modes == NULL)
		return;

	for (i = 0; i < wpa_s->hw.num_modes; i++) {
		os_free(wpa_s->hw.modes[i].channels);
		os_free(wpa_s->hw.modes[i].rates);
	}

	os_free(wpa_s->hw.modes);
	wpa_s->hw.modes = NULL;
}
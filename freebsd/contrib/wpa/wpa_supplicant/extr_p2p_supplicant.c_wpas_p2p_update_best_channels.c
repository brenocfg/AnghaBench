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
struct wpa_supplicant {TYPE_1__* global; } ;
struct p2p_data {int dummy; } ;
struct TYPE_2__ {struct p2p_data* p2p; } ;

/* Variables and functions */
 int /*<<< orphan*/  p2p_set_best_channels (struct p2p_data*,int,int,int) ; 

void wpas_p2p_update_best_channels(struct wpa_supplicant *wpa_s,
				   int freq_24, int freq_5, int freq_overall)
{
	struct p2p_data *p2p = wpa_s->global->p2p;
	if (p2p == NULL)
		return;
	p2p_set_best_channels(p2p, freq_24, freq_5, freq_overall);
}
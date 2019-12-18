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
struct p2p_channels {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  p2p; } ;

/* Variables and functions */
 scalar_t__ freq_included (struct wpa_supplicant*,struct p2p_channels const*,int) ; 
 scalar_t__ p2p_supported_freq_go (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpas_p2p_disallowed_freq (TYPE_1__*,int) ; 

__attribute__((used)) static int wpas_p2p_supported_freq_go(struct wpa_supplicant *wpa_s,
				      const struct p2p_channels *channels,
				      int freq)
{
	if (!wpas_p2p_disallowed_freq(wpa_s->global, freq) &&
	    p2p_supported_freq_go(wpa_s->global->p2p, freq) &&
	    freq_included(wpa_s, channels, freq))
		return 1;
	return 0;
}
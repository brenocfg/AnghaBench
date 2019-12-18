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
struct wpa_global {int /*<<< orphan*/  p2p_disallow_freq; int /*<<< orphan*/  p2p_go_avoid_freq; } ;

/* Variables and functions */
 int freq_range_list_includes (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int wpas_p2p_disallowed_freq(struct wpa_global *global,
				    unsigned int freq)
{
	if (freq_range_list_includes(&global->p2p_go_avoid_freq, freq))
		return 1;
	return freq_range_list_includes(&global->p2p_disallow_freq, freq);
}
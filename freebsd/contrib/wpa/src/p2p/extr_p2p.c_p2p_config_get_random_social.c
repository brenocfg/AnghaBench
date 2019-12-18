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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_freq_range_list {int dummy; } ;
struct p2p_config {int /*<<< orphan*/  channels; } ;

/* Variables and functions */
 int p2p_channel_random_social (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct wpa_freq_range_list*,struct wpa_freq_range_list*) ; 

int p2p_config_get_random_social(struct p2p_config *p2p, u8 *op_class,
				 u8 *op_channel,
				 struct wpa_freq_range_list *avoid_list,
				 struct wpa_freq_range_list *disallow_list)
{
	return p2p_channel_random_social(&p2p->channels, op_class, op_channel,
					 avoid_list, disallow_list);
}
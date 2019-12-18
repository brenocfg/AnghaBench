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
struct wpa_mbo_non_pref_channel {scalar_t__ oper_class; scalar_t__ chan; } ;

/* Variables and functions */

__attribute__((used)) static int wpa_non_pref_chan_is_eq(struct wpa_mbo_non_pref_channel *a,
				   struct wpa_mbo_non_pref_channel *b)
{
	return a->oper_class == b->oper_class && a->chan == b->chan;
}
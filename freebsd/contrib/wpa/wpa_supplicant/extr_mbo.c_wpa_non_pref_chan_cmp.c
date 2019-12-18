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
struct wpa_mbo_non_pref_channel {scalar_t__ oper_class; scalar_t__ reason; scalar_t__ preference; } ;

/* Variables and functions */

__attribute__((used)) static int wpa_non_pref_chan_cmp(const void *_a, const void *_b)
{
	const struct wpa_mbo_non_pref_channel *a = _a, *b = _b;

	if (a->oper_class != b->oper_class)
		return (int) a->oper_class - (int) b->oper_class;
	if (a->reason != b->reason)
		return (int) a->reason - (int) b->reason;
	return (int) a->preference - (int) b->preference;
}
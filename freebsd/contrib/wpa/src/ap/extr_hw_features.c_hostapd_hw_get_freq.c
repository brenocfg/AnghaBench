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
struct hostapd_data {TYPE_1__* iface; } ;
struct TYPE_2__ {int /*<<< orphan*/  current_mode; } ;

/* Variables and functions */
 int hw_get_freq (int /*<<< orphan*/ ,int) ; 

int hostapd_hw_get_freq(struct hostapd_data *hapd, int chan)
{
	return hw_get_freq(hapd->iface->current_mode, chan);
}
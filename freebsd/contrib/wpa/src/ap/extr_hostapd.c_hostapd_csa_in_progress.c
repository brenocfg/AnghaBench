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
struct hostapd_iface {unsigned int num_bss; TYPE_1__** bss; } ;
struct TYPE_2__ {scalar_t__ csa_in_progress; } ;

/* Variables and functions */

int hostapd_csa_in_progress(struct hostapd_iface *iface)
{
	unsigned int i;

	for (i = 0; i < iface->num_bss; i++)
		if (iface->bss[i]->csa_in_progress)
			return 1;
	return 0;
}
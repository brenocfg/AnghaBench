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
struct hostapd_iface {struct ap_info* ap_list; } ;
struct ap_info {TYPE_1__* prev; struct ap_info* next; } ;
struct TYPE_2__ {struct ap_info* next; } ;

/* Variables and functions */

__attribute__((used)) static void ap_ap_list_del(struct hostapd_iface *iface, struct ap_info *ap)
{
	if (iface->ap_list == ap)
		iface->ap_list = ap->next;
	else
		ap->prev->next = ap->next;

	if (ap->next)
		ap->next->prev = ap->prev;
	else if (iface->ap_list)
		iface->ap_list->prev = ap->prev;
}
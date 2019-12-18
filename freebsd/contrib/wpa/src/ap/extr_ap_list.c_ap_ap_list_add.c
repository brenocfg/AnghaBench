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
struct hostapd_iface {struct ap_info* ap_list; } ;
struct ap_info {struct ap_info* next; struct ap_info* prev; } ;

/* Variables and functions */

__attribute__((used)) static void ap_ap_list_add(struct hostapd_iface *iface, struct ap_info *ap)
{
	if (iface->ap_list) {
		ap->prev = iface->ap_list->prev;
		iface->ap_list->prev = ap;
	} else
		ap->prev = ap;
	ap->next = iface->ap_list;
	iface->ap_list = ap;
}
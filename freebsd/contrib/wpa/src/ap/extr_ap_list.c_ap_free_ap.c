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
struct hostapd_iface {int /*<<< orphan*/  num_ap; } ;
struct ap_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ap_ap_hash_del (struct hostapd_iface*,struct ap_info*) ; 
 int /*<<< orphan*/  ap_ap_list_del (struct hostapd_iface*,struct ap_info*) ; 
 int /*<<< orphan*/  os_free (struct ap_info*) ; 

__attribute__((used)) static void ap_free_ap(struct hostapd_iface *iface, struct ap_info *ap)
{
	ap_ap_hash_del(iface, ap);
	ap_ap_list_del(iface, ap);

	iface->num_ap--;
	os_free(ap);
}
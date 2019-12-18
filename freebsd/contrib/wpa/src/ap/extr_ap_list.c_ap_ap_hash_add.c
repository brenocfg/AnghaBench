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
struct hostapd_iface {struct ap_info** ap_hash; } ;
struct ap_info {int /*<<< orphan*/  addr; struct ap_info* hnext; } ;

/* Variables and functions */
 size_t STA_HASH (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ap_ap_hash_add(struct hostapd_iface *iface, struct ap_info *ap)
{
	ap->hnext = iface->ap_hash[STA_HASH(ap->addr)];
	iface->ap_hash[STA_HASH(ap->addr)] = ap;
}
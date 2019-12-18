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
struct hostapd_iface {struct ap_info** ap_hash; } ;
struct ap_info {struct ap_info* hnext; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 size_t STA_HASH (int /*<<< orphan*/  const*) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ap_info * ap_get_ap(struct hostapd_iface *iface, const u8 *ap)
{
	struct ap_info *s;

	s = iface->ap_hash[STA_HASH(ap)];
	while (s != NULL && os_memcmp(s->addr, ap, ETH_ALEN) != 0)
		s = s->hnext;
	return s;
}
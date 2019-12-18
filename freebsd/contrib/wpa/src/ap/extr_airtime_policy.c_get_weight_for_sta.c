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
typedef  int /*<<< orphan*/  u8 ;
struct hostapd_data {TYPE_1__* conf; } ;
struct airtime_sta_weight {int weight; struct airtime_sta_weight* next; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int airtime_weight; struct airtime_sta_weight* airtime_weight_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_weight_for_sta(struct hostapd_data *hapd, const u8 *sta)
{
	struct airtime_sta_weight *wt;

	wt = hapd->conf->airtime_weight_list;
	while (wt && os_memcmp(wt->addr, sta, ETH_ALEN) != 0)
		wt = wt->next;

	return wt ? wt->weight : hapd->conf->airtime_weight;
}
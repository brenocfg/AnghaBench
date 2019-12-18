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
typedef  int /*<<< orphan*/  uint32_t ;
struct ieee80211req_sta_info {int dummy; } ;
struct TYPE_2__ {size_t len; } ;
struct ieee80211_node {TYPE_1__ ni_ies; } ;

/* Variables and functions */
 size_t roundup (int,int) ; 

__attribute__((used)) static size_t
sta_space(const struct ieee80211_node *ni, size_t *ielen)
{
	*ielen = ni->ni_ies.len;
	return roundup(sizeof(struct ieee80211req_sta_info) + *ielen,
		      sizeof(uint32_t));
}
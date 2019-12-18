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
typedef  scalar_t__ uint16_t ;
struct ieee80211_node {scalar_t__ ni_mllid; } ;

/* Variables and functions */

__attribute__((used)) static void
mesh_checkid(void *arg, struct ieee80211_node *ni)
{
	uint16_t *r = arg;
	
	if (*r == ni->ni_mllid)
		*(uint16_t *)arg = 0;
}
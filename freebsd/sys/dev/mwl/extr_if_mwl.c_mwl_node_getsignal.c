#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_node {TYPE_1__* ni_ic; } ;
typedef  int int8_t ;
struct TYPE_5__ {int nf; } ;
struct TYPE_6__ {TYPE_2__ mn_ai; } ;
struct TYPE_4__ {int (* ic_node_getrssi ) (struct ieee80211_node const*) ;} ;

/* Variables and functions */
 TYPE_3__* MWL_NODE_CONST (struct ieee80211_node const*) ; 
 int stub1 (struct ieee80211_node const*) ; 

__attribute__((used)) static void
mwl_node_getsignal(const struct ieee80211_node *ni, int8_t *rssi, int8_t *noise)
{
	*rssi = ni->ni_ic->ic_node_getrssi(ni);
#ifdef MWL_ANT_INFO_SUPPORT
#if 0
	/* XXX need to smooth data */
	*noise = -MWL_NODE_CONST(ni)->mn_ai.nf;
#else
	*noise = -95;		/* XXX */
#endif
#else
	*noise = -95;		/* XXX */
#endif
}
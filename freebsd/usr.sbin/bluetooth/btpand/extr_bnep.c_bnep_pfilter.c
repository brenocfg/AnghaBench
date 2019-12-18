#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int len; scalar_t__ ptr; scalar_t__ type; } ;
typedef  TYPE_2__ packet_t ;
struct TYPE_8__ {int npfilter; TYPE_1__* pfilter; } ;
typedef  TYPE_3__ channel_t ;
struct TYPE_6__ {int start; int end; } ;

/* Variables and functions */
 int ETHERTYPE_VLAN ; 
 int be16dec (scalar_t__) ; 

__attribute__((used)) static bool
bnep_pfilter(channel_t *chan, packet_t *pkt)
{
	int proto, i;

	proto = be16dec(pkt->type);
	if (proto == ETHERTYPE_VLAN) {	/* IEEE 802.1Q tag header */
		if (pkt->len < 4)
			return false;

		proto = be16dec(pkt->ptr + 2);
	}

	for (i = 0; i < chan->npfilter; i++) {
		if (chan->pfilter[i].start <= proto
		    && chan->pfilter[i].end >=proto)
			return true;
	}

	return false;
}
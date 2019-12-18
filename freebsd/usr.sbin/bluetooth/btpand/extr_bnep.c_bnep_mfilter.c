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
struct TYPE_7__ {int /*<<< orphan*/  dst; } ;
typedef  TYPE_2__ packet_t ;
struct TYPE_8__ {int nmfilter; TYPE_1__* mfilter; } ;
typedef  TYPE_3__ channel_t ;
struct TYPE_6__ {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  ETHER_IS_MULTICAST (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
bnep_mfilter(channel_t *chan, packet_t *pkt)
{
	int i;

	if (!ETHER_IS_MULTICAST(pkt->dst))
		return true;

	for (i = 0; i < chan->nmfilter; i++) {
		if (memcmp(pkt->dst, chan->mfilter[i].start, ETHER_ADDR_LEN) >= 0
		    && memcmp(pkt->dst, chan->mfilter[i].end, ETHER_ADDR_LEN) <= 0)
			return true;
	}

	return false;
}
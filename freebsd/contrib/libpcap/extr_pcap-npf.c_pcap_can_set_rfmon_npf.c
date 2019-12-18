#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct TYPE_5__ {TYPE_1__ opt; } ;
typedef  TYPE_2__ pcap_t ;

/* Variables and functions */
 int PacketIsMonitorModeSupported (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pcap_can_set_rfmon_npf(pcap_t *p)
{
	return (PacketIsMonitorModeSupported(p->opt.device) == 1);
}
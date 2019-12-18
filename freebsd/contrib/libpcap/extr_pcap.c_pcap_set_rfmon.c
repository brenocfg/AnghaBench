#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int rfmon; } ;
struct TYPE_6__ {TYPE_1__ opt; } ;
typedef  TYPE_2__ pcap_t ;

/* Variables and functions */
 int PCAP_ERROR_ACTIVATED ; 
 scalar_t__ pcap_check_activated (TYPE_2__*) ; 

int
pcap_set_rfmon(pcap_t *p, int rfmon)
{
	if (pcap_check_activated(p))
		return (PCAP_ERROR_ACTIVATED);
	p->opt.rfmon = rfmon;
	return (0);
}
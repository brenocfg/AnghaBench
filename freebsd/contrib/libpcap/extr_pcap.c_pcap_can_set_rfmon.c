#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int (* can_set_rfmon_op ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int stub1 (TYPE_1__*) ; 

int
pcap_can_set_rfmon(pcap_t *p)
{
	return (p->can_set_rfmon_op(p));
}
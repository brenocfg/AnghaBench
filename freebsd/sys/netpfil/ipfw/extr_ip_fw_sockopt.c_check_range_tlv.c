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
struct TYPE_4__ {int length; } ;
struct TYPE_5__ {scalar_t__ start_rule; scalar_t__ end_rule; scalar_t__ set; scalar_t__ new_set; int flags; TYPE_1__ head; } ;
typedef  TYPE_2__ ipfw_range_tlv ;

/* Variables and functions */
 scalar_t__ IPFW_MAX_SETS ; 
 int IPFW_RCFLAG_USER ; 

__attribute__((used)) static int
check_range_tlv(ipfw_range_tlv *rt)
{

	if (rt->head.length != sizeof(*rt))
		return (1);
	if (rt->start_rule > rt->end_rule)
		return (1);
	if (rt->set >= IPFW_MAX_SETS || rt->new_set >= IPFW_MAX_SETS)
		return (1);

	if ((rt->flags & IPFW_RCFLAG_USER) != rt->flags)
		return (1);

	return (0);
}
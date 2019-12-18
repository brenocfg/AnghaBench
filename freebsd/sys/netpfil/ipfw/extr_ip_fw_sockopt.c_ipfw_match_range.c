#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ip_fw {scalar_t__ rulenum; scalar_t__ set; } ;
struct TYPE_3__ {int flags; scalar_t__ set; scalar_t__ start_rule; scalar_t__ end_rule; } ;
typedef  TYPE_1__ ipfw_range_tlv ;

/* Variables and functions */
 scalar_t__ IPFW_DEFAULT_RULE ; 
 int IPFW_RCFLAG_ALL ; 
 int IPFW_RCFLAG_DEFAULT ; 
 int IPFW_RCFLAG_RANGE ; 
 int IPFW_RCFLAG_SET ; 
 scalar_t__ RESVD_SET ; 

int
ipfw_match_range(struct ip_fw *rule, ipfw_range_tlv *rt)
{

	/* Don't match default rule for modification queries */
	if (rule->rulenum == IPFW_DEFAULT_RULE &&
	    (rt->flags & IPFW_RCFLAG_DEFAULT) == 0)
		return (0);

	/* Don't match rules in reserved set for flush requests */
	if ((rt->flags & IPFW_RCFLAG_ALL) != 0 && rule->set == RESVD_SET)
		return (0);

	/* If we're filtering by set, don't match other sets */
	if ((rt->flags & IPFW_RCFLAG_SET) != 0 && rule->set != rt->set)
		return (0);

	if ((rt->flags & IPFW_RCFLAG_RANGE) != 0 &&
	    (rule->rulenum < rt->start_rule || rule->rulenum > rt->end_rule))
		return (0);

	return (1);
}
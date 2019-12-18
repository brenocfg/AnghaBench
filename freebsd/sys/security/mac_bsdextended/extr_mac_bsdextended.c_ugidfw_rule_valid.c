#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int mbo_flags; int mbo_neg; int mbo_type; } ;
struct TYPE_3__ {int mbs_flags; int mbs_neg; } ;
struct mac_bsdextended_rule {int mbr_mode; TYPE_2__ mbr_object; TYPE_1__ mbr_subject; } ;

/* Variables and functions */
 int EINVAL ; 
 int MBI_ALLPERM ; 
 int MBO_ALL_FLAGS ; 
 int MBO_ALL_TYPE ; 
 int MBO_TYPE_DEFINED ; 
 int MBS_ALL_FLAGS ; 

__attribute__((used)) static int
ugidfw_rule_valid(struct mac_bsdextended_rule *rule)
{

	if ((rule->mbr_subject.mbs_flags | MBS_ALL_FLAGS) != MBS_ALL_FLAGS)
		return (EINVAL);
	if ((rule->mbr_subject.mbs_neg | MBS_ALL_FLAGS) != MBS_ALL_FLAGS)
		return (EINVAL);
	if ((rule->mbr_object.mbo_flags | MBO_ALL_FLAGS) != MBO_ALL_FLAGS)
		return (EINVAL);
	if ((rule->mbr_object.mbo_neg | MBO_ALL_FLAGS) != MBO_ALL_FLAGS)
		return (EINVAL);
	if (((rule->mbr_object.mbo_flags & MBO_TYPE_DEFINED) != 0) &&
	    (rule->mbr_object.mbo_type | MBO_ALL_TYPE) != MBO_ALL_TYPE)
		return (EINVAL);
	if ((rule->mbr_mode | MBI_ALLPERM) != MBI_ALLPERM)
		return (EINVAL);
	return (0);
}
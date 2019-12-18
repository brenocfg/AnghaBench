#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct ip_fw_chain {int dummy; } ;
typedef  int /*<<< orphan*/  rt ;
struct TYPE_6__ {int start_rule; int end_rule; int set; int new_set; int flags; } ;
typedef  TYPE_1__ ipfw_range_tlv ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUP ; 
 int IPFW_DEFAULT_RULE ; 
 int IPFW_RCFLAG_ALL ; 
 int IPFW_RCFLAG_RANGE ; 
 int IPFW_RCFLAG_SET ; 
 int /*<<< orphan*/  IPFW_UH_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_WUNLOCK (struct ip_fw_chain*) ; 
 int RESVD_SET ; 
 int delete_range (struct ip_fw_chain*,TYPE_1__*,int*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int move_range (struct ip_fw_chain*,TYPE_1__*) ; 
 int swap_sets (struct ip_fw_chain*,TYPE_1__*,int) ; 

__attribute__((used)) static int
del_entry(struct ip_fw_chain *chain, uint32_t arg)
{
	uint32_t num;	/* rule number or old_set */
	uint8_t cmd, new_set;
	int do_del, ndel;
	int error = 0;
	ipfw_range_tlv rt;

	num = arg & 0xffff;
	cmd = (arg >> 24) & 0xff;
	new_set = (arg >> 16) & 0xff;

	if (cmd > 5 || new_set > RESVD_SET)
		return EINVAL;
	if (cmd == 0 || cmd == 2 || cmd == 5) {
		if (num >= IPFW_DEFAULT_RULE)
			return EINVAL;
	} else {
		if (num > RESVD_SET)	/* old_set */
			return EINVAL;
	}

	/* Convert old requests into new representation */
	memset(&rt, 0, sizeof(rt));
	rt.start_rule = num;
	rt.end_rule = num;
	rt.set = num;
	rt.new_set = new_set;
	do_del = 0;

	switch (cmd) {
	case 0: /* delete rules numbered "rulenum" */
		if (num == 0)
			rt.flags |= IPFW_RCFLAG_ALL;
		else
			rt.flags |= IPFW_RCFLAG_RANGE;
		do_del = 1;
		break;
	case 1: /* delete rules in set "rulenum" */
		rt.flags |= IPFW_RCFLAG_SET;
		do_del = 1;
		break;
	case 5: /* delete rules "rulenum" and set "new_set" */
		rt.flags |= IPFW_RCFLAG_RANGE | IPFW_RCFLAG_SET;
		rt.set = new_set;
		rt.new_set = 0;
		do_del = 1;
		break;
	case 2: /* move rules "rulenum" to set "new_set" */
		rt.flags |= IPFW_RCFLAG_RANGE;
		break;
	case 3: /* move rules from set "rulenum" to set "new_set" */
		IPFW_UH_WLOCK(chain);
		error = swap_sets(chain, &rt, 1);
		IPFW_UH_WUNLOCK(chain);
		return (error);
	case 4: /* swap sets "rulenum" and "new_set" */
		IPFW_UH_WLOCK(chain);
		error = swap_sets(chain, &rt, 0);
		IPFW_UH_WUNLOCK(chain);
		return (error);
	default:
		return (ENOTSUP);
	}

	if (do_del != 0) {
		if ((error = delete_range(chain, &rt, &ndel)) != 0)
			return (error);

		if (ndel == 0 && (cmd != 1 && num != 0))
			return (EINVAL);

		return (0);
	}

	return (move_range(chain, &rt));
}
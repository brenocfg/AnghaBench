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
typedef  scalar_t__ uint8_t ;
struct opcode_obj_rewrite {int (* manage_sets ) (struct ip_fw_chain*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ;} ;
struct ip_fw_chain {int n_rules; struct ip_fw** map; } ;
struct ip_fw {scalar_t__ set; } ;
struct TYPE_3__ {scalar_t__ set; scalar_t__ new_set; } ;
typedef  TYPE_1__ ipfw_range_tlv ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  IPFW_UH_WLOCK_ASSERT (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  MOVE_ALL ; 
 int /*<<< orphan*/  SWAP_ALL ; 
 int /*<<< orphan*/  TEST_ALL ; 
 struct opcode_obj_rewrite* ctl3_rewriters ; 
 int ctl3_rsize ; 
 int stub1 (struct ip_fw_chain*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int stub2 (struct ip_fw_chain*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
swap_sets(struct ip_fw_chain *chain, ipfw_range_tlv *rt, int mv)
{
	struct opcode_obj_rewrite *rw;
	struct ip_fw *rule;
	int i;

	IPFW_UH_WLOCK_ASSERT(chain);

	if (rt->set == rt->new_set) /* nothing to do */
		return (0);

	if (mv != 0) {
		/*
		 * Berfore moving the rules we need to check that
		 * there aren't any conflicting named objects.
		 */
		for (rw = ctl3_rewriters;
		    rw < ctl3_rewriters + ctl3_rsize; rw++) {
			if (rw->manage_sets == NULL)
				continue;
			i = rw->manage_sets(chain, (uint8_t)rt->set,
			    (uint8_t)rt->new_set, TEST_ALL);
			if (i != 0)
				return (EEXIST);
		}
	}
	/* Swap or move two sets */
	for (i = 0; i < chain->n_rules - 1; i++) {
		rule = chain->map[i];
		if (rule->set == (uint8_t)rt->set)
			rule->set = (uint8_t)rt->new_set;
		else if (rule->set == (uint8_t)rt->new_set && mv == 0)
			rule->set = (uint8_t)rt->set;
	}
	for (rw = ctl3_rewriters; rw < ctl3_rewriters + ctl3_rsize; rw++) {
		if (rw->manage_sets == NULL)
			continue;
		rw->manage_sets(chain, (uint8_t)rt->set,
		    (uint8_t)rt->new_set, mv != 0 ? MOVE_ALL: SWAP_ALL);
	}
	return (0);
}
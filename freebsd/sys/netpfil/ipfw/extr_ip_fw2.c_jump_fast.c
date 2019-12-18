#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ip_fw_chain {scalar_t__ id; int* idxmap; } ;
struct ip_fw {scalar_t__ cached_id; int cached_pos; int rulenum; } ;

/* Variables and functions */
 int IP_FW_ARG_TABLEARG (struct ip_fw_chain*,int,int /*<<< orphan*/ ) ; 
 int IP_FW_TARG ; 
 int ipfw_find_rule (struct ip_fw_chain*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skipto ; 

__attribute__((used)) static int
jump_fast(struct ip_fw_chain *chain, struct ip_fw *f, int num,
    int tablearg, int jump_backwards)
{
	int f_pos;

	/* If possible use cached f_pos (in f->cached_pos),
	 * whose version is written in f->cached_id
	 * (horrible hacks to avoid changing the ABI).
	 */
	if (num != IP_FW_TARG && f->cached_id == chain->id)
		f_pos = f->cached_pos;
	else {
		int i = IP_FW_ARG_TABLEARG(chain, num, skipto);
		/* make sure we do not jump backward */
		if (jump_backwards == 0 && i <= f->rulenum)
			i = f->rulenum + 1;
		if (chain->idxmap != NULL)
			f_pos = chain->idxmap[i];
		else
			f_pos = ipfw_find_rule(chain, i, 0);
		/* update the cache */
		if (num != IP_FW_TARG) {
			f->cached_id = chain->id;
			f->cached_pos = f_pos;
		}
	}

	return (f_pos);
}
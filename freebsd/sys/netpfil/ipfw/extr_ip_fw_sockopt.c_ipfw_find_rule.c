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
typedef  scalar_t__ uint32_t ;
struct ip_fw_chain {int n_rules; struct ip_fw** map; } ;
struct ip_fw {scalar_t__ rulenum; scalar_t__ id; } ;

/* Variables and functions */

int
ipfw_find_rule(struct ip_fw_chain *chain, uint32_t key, uint32_t id)
{
	int i, lo, hi;
	struct ip_fw *r;

  	for (lo = 0, hi = chain->n_rules - 1; lo < hi;) {
		i = (lo + hi) / 2;
		r = chain->map[i];
		if (r->rulenum < key)
			lo = i + 1;	/* continue from the next one */
		else if (r->rulenum > key)
			hi = i;		/* this might be good */
		else if (r->id < id)
			lo = i + 1;	/* continue from the next one */
		else /* r->id >= id */
			hi = i;		/* this might be good */
	}
	return hi;
}
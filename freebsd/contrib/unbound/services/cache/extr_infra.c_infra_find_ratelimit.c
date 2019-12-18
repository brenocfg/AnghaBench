#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct infra_cache {int /*<<< orphan*/  domain_limits; } ;
struct TYPE_2__ {int labs; scalar_t__ parent; } ;
struct domain_limit_data {int lim; int below; TYPE_1__ node; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_CLASS_IN ; 
 int dname_count_labels (int /*<<< orphan*/ *) ; 
 int infra_dp_ratelimit ; 
 scalar_t__ name_tree_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ) ; 

int infra_find_ratelimit(struct infra_cache* infra, uint8_t* name,
	size_t namelen)
{
	int labs = dname_count_labels(name);
	struct domain_limit_data* d = (struct domain_limit_data*)
		name_tree_lookup(&infra->domain_limits, name, namelen, labs,
		LDNS_RR_CLASS_IN);
	if(!d) return infra_dp_ratelimit;

	if(d->node.labs == labs && d->lim != -1)
		return d->lim; /* exact match */

	/* find 'below match' */
	if(d->node.labs == labs)
		d = (struct domain_limit_data*)d->node.parent;
	while(d) {
		if(d->below != -1)
			return d->below;
		d = (struct domain_limit_data*)d->node.parent;
	}
	return infra_dp_ratelimit;
}
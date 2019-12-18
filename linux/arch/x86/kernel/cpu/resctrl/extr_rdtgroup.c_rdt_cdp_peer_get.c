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
struct rdt_resource {int rid; } ;
struct rdt_domain {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct rdt_domain*) ; 
#define  RDT_RESOURCE_L2CODE 131 
#define  RDT_RESOURCE_L2DATA 130 
#define  RDT_RESOURCE_L3CODE 129 
#define  RDT_RESOURCE_L3DATA 128 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 struct rdt_domain* rdt_find_domain (struct rdt_resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct rdt_resource* rdt_resources_all ; 

__attribute__((used)) static int rdt_cdp_peer_get(struct rdt_resource *r, struct rdt_domain *d,
			    struct rdt_resource **r_cdp,
			    struct rdt_domain **d_cdp)
{
	struct rdt_resource *_r_cdp = NULL;
	struct rdt_domain *_d_cdp = NULL;
	int ret = 0;

	switch (r->rid) {
	case RDT_RESOURCE_L3DATA:
		_r_cdp = &rdt_resources_all[RDT_RESOURCE_L3CODE];
		break;
	case RDT_RESOURCE_L3CODE:
		_r_cdp =  &rdt_resources_all[RDT_RESOURCE_L3DATA];
		break;
	case RDT_RESOURCE_L2DATA:
		_r_cdp =  &rdt_resources_all[RDT_RESOURCE_L2CODE];
		break;
	case RDT_RESOURCE_L2CODE:
		_r_cdp =  &rdt_resources_all[RDT_RESOURCE_L2DATA];
		break;
	default:
		ret = -ENOENT;
		goto out;
	}

	/*
	 * When a new CPU comes online and CDP is enabled then the new
	 * RDT domains (if any) associated with both CDP RDT resources
	 * are added in the same CPU online routine while the
	 * rdtgroup_mutex is held. It should thus not happen for one
	 * RDT domain to exist and be associated with its RDT CDP
	 * resource but there is no RDT domain associated with the
	 * peer RDT CDP resource. Hence the WARN.
	 */
	_d_cdp = rdt_find_domain(_r_cdp, d->id, NULL);
	if (WARN_ON(IS_ERR_OR_NULL(_d_cdp))) {
		_r_cdp = NULL;
		ret = -EINVAL;
	}

out:
	*r_cdp = _r_cdp;
	*d_cdp = _d_cdp;

	return ret;
}
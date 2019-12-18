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
struct TYPE_3__ {TYPE_2__* key; } ;
struct TYPE_4__ {size_t len; int labs; int /*<<< orphan*/  dclass; struct domain_limit_data* name; TYPE_1__ node; } ;
struct domain_limit_data {int lim; int below; TYPE_2__ node; } ;
typedef  struct domain_limit_data uint8_t ;
struct infra_cache {int /*<<< orphan*/  domain_limits; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_CLASS_IN ; 
 scalar_t__ calloc (int,int) ; 
 int dname_count_labels (struct domain_limit_data*) ; 
 int /*<<< orphan*/  free (struct domain_limit_data*) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 scalar_t__ name_tree_find (int /*<<< orphan*/ *,struct domain_limit_data*,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  name_tree_insert (int /*<<< orphan*/ *,TYPE_2__*,struct domain_limit_data*,size_t,int,int /*<<< orphan*/ ) ; 
 struct domain_limit_data* sldns_str2wire_dname (char*,size_t*) ; 

__attribute__((used)) static struct domain_limit_data* domain_limit_findcreate(
	struct infra_cache* infra, char* name)
{
	uint8_t* nm;
	int labs;
	size_t nmlen;
	struct domain_limit_data* d;

	/* parse name */
	nm = sldns_str2wire_dname(name, &nmlen);
	if(!nm) {
		log_err("could not parse %s", name);
		return NULL;
	}
	labs = dname_count_labels(nm);

	/* can we find it? */
	d = (struct domain_limit_data*)name_tree_find(&infra->domain_limits,
		nm, nmlen, labs, LDNS_RR_CLASS_IN);
	if(d) {
		free(nm);
		return d;
	}
	
	/* create it */
	d = (struct domain_limit_data*)calloc(1, sizeof(*d));
	if(!d) {
		free(nm);
		return NULL;
	}
	d->node.node.key = &d->node;
	d->node.name = nm;
	d->node.len = nmlen;
	d->node.labs = labs;
	d->node.dclass = LDNS_RR_CLASS_IN;
	d->lim = -1;
	d->below = -1;
	if(!name_tree_insert(&infra->domain_limits, &d->node, nm, nmlen,
		labs, LDNS_RR_CLASS_IN)) {
		log_err("duplicate element in domainlimit tree");
		free(nm);
		free(d);
		return NULL;
	}
	return d;
}
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
typedef  scalar_t__ uint16_t ;
struct iter_forwards {int /*<<< orphan*/  tree; } ;
struct TYPE_2__ {struct iter_forward_zone* key; } ;
struct iter_forward_zone {scalar_t__ dclass; int namelabs; struct delegpt* dp; struct iter_forward_zone* parent; int /*<<< orphan*/ * name; int /*<<< orphan*/  namelen; TYPE_1__ node; } ;
struct delegpt {int dummy; } ;
typedef  int /*<<< orphan*/  rbnode_type ;

/* Variables and functions */
 int dname_count_size_labels (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dname_lab_cmp (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int*) ; 
 scalar_t__ rbtree_find_less_equal (int /*<<< orphan*/ ,struct iter_forward_zone*,int /*<<< orphan*/ **) ; 

struct delegpt* 
forwards_lookup(struct iter_forwards* fwd, uint8_t* qname, uint16_t qclass)
{
	/* lookup the forward zone in the tree */
	rbnode_type* res = NULL;
	struct iter_forward_zone *result;
	struct iter_forward_zone key;
	key.node.key = &key;
	key.dclass = qclass;
	key.name = qname;
	key.namelabs = dname_count_size_labels(qname, &key.namelen);
	if(rbtree_find_less_equal(fwd->tree, &key, &res)) {
		/* exact */
		result = (struct iter_forward_zone*)res;
	} else {
		/* smaller element (or no element) */
		int m;
		result = (struct iter_forward_zone*)res;
		if(!result || result->dclass != qclass)
			return NULL;
		/* count number of labels matched */
		(void)dname_lab_cmp(result->name, result->namelabs, key.name,
			key.namelabs, &m);
		while(result) { /* go up until qname is subdomain of stub */
			if(result->namelabs <= m)
				break;
			result = result->parent;
		}
	}
	if(result)
		return result->dp;
	return NULL;
}
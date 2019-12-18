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
struct TYPE_2__ {struct val_neg_zone* key; } ;
struct val_neg_zone {size_t len; int labs; scalar_t__ dclass; struct val_neg_zone* parent; int /*<<< orphan*/ * name; TYPE_1__ node; } ;
struct val_neg_cache {int /*<<< orphan*/  tree; } ;
typedef  int /*<<< orphan*/  rbnode_type ;

/* Variables and functions */
 int /*<<< orphan*/  dname_lab_cmp (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int*) ; 
 scalar_t__ rbtree_find_less_equal (int /*<<< orphan*/ *,struct val_neg_zone*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static struct val_neg_zone* neg_closest_zone_parent(struct val_neg_cache* neg,
	uint8_t* nm, size_t nm_len, int labs, uint16_t qclass)
{
	struct val_neg_zone key;
	struct val_neg_zone* result;
	rbnode_type* res = NULL;
	key.node.key = &key;
	key.name = nm;
	key.len = nm_len;
	key.labs = labs;
	key.dclass = qclass;
	if(rbtree_find_less_equal(&neg->tree, &key, &res)) {
		/* exact match */
		result = (struct val_neg_zone*)res;
	} else {
		/* smaller element (or no element) */
		int m;
		result = (struct val_neg_zone*)res;
		if(!result || result->dclass != qclass)
			return NULL;
		/* count number of labels matched */
		(void)dname_lab_cmp(result->name, result->labs, key.name,
			key.labs, &m);
		while(result) { /* go up until qname is subdomain of stub */
			if(result->labs <= m)
				break;
			result = result->parent;
		}
	}
	return result;
}
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
struct val_neg_zone {int /*<<< orphan*/  tree; } ;
struct TYPE_2__ {struct val_neg_data* key; } ;
struct val_neg_data {size_t len; int labs; struct val_neg_data* parent; int /*<<< orphan*/ * name; TYPE_1__ node; } ;
typedef  int /*<<< orphan*/  rbnode_type ;

/* Variables and functions */
 int /*<<< orphan*/  dname_lab_cmp (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int*) ; 
 scalar_t__ rbtree_find_less_equal (int /*<<< orphan*/ *,struct val_neg_data*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static struct val_neg_data* neg_closest_data_parent(
	struct val_neg_zone* zone, uint8_t* nm, size_t nm_len, int labs)
{
	struct val_neg_data key;
	struct val_neg_data* result;
	rbnode_type* res = NULL;
	key.node.key = &key;
	key.name = nm;
	key.len = nm_len;
	key.labs = labs;
	if(rbtree_find_less_equal(&zone->tree, &key, &res)) {
		/* exact match */
		result = (struct val_neg_data*)res;
	} else {
		/* smaller element (or no element) */
		int m;
		result = (struct val_neg_data*)res;
		if(!result)
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
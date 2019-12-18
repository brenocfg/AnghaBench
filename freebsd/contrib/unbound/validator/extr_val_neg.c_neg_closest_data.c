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
struct val_neg_data {size_t len; int labs; int /*<<< orphan*/ * name; TYPE_1__ node; } ;
typedef  int /*<<< orphan*/  rbnode_type ;

/* Variables and functions */
 scalar_t__ rbtree_find_less_equal (int /*<<< orphan*/ *,struct val_neg_data*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int neg_closest_data(struct val_neg_zone* zone,
	uint8_t* qname, size_t len, int labs, struct val_neg_data** data)
{
	struct val_neg_data key;
	rbnode_type* r;
	key.node.key = &key;
	key.name = qname;
	key.len = len;
	key.labs = labs;
	if(rbtree_find_less_equal(&zone->tree, &key, &r)) {
		/* exact match */
		*data = (struct val_neg_data*)r;
		return 1;
	} else {
		/* smaller match */
		*data = (struct val_neg_data*)r;
		return 0;
	}
}
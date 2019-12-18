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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {struct val_neg_zone* key; } ;
struct val_neg_zone {size_t len; TYPE_1__ node; int /*<<< orphan*/  dclass; int /*<<< orphan*/ * name; int /*<<< orphan*/  labs; } ;
struct val_neg_cache {int /*<<< orphan*/  tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  dname_count_labels (int /*<<< orphan*/ *) ; 
 scalar_t__ rbtree_search (int /*<<< orphan*/ *,struct val_neg_zone*) ; 

struct val_neg_zone* neg_find_zone(struct val_neg_cache* neg, 
	uint8_t* nm, size_t len, uint16_t dclass)
{
	struct val_neg_zone lookfor;
	struct val_neg_zone* result;
	lookfor.node.key = &lookfor;
	lookfor.name = nm;
	lookfor.len = len;
	lookfor.labs = dname_count_labels(lookfor.name);
	lookfor.dclass = dclass;

	result = (struct val_neg_zone*)
		rbtree_search(&neg->tree, lookfor.node.key);
	return result;
}
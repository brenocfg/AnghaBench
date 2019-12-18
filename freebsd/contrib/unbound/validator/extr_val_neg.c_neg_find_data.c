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
struct val_neg_data {size_t len; int labs; TYPE_1__ node; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 scalar_t__ rbtree_search (int /*<<< orphan*/ *,struct val_neg_data*) ; 

__attribute__((used)) static struct val_neg_data* neg_find_data(struct val_neg_zone* zone, 
	uint8_t* nm, size_t len, int labs)
{
	struct val_neg_data lookfor;
	struct val_neg_data* result;
	lookfor.node.key = &lookfor;
	lookfor.name = nm;
	lookfor.len = len;
	lookfor.labs = labs;

	result = (struct val_neg_data*)
		rbtree_search(&zone->tree, lookfor.node.key);
	return result;
}
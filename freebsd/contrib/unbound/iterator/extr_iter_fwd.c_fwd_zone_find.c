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
struct iter_forwards {int /*<<< orphan*/  tree; } ;
struct TYPE_2__ {struct iter_forward_zone* key; } ;
struct iter_forward_zone {int /*<<< orphan*/  namelen; int /*<<< orphan*/  namelabs; int /*<<< orphan*/ * name; int /*<<< orphan*/  dclass; TYPE_1__ node; } ;

/* Variables and functions */
 int /*<<< orphan*/  dname_count_size_labels (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ rbtree_search (int /*<<< orphan*/ ,struct iter_forward_zone*) ; 

__attribute__((used)) static struct iter_forward_zone*
fwd_zone_find(struct iter_forwards* fwd, uint16_t c, uint8_t* nm)
{
	struct iter_forward_zone key;
	key.node.key = &key;
	key.dclass = c;
	key.name = nm;
	key.namelabs = dname_count_size_labels(nm, &key.namelen);
	return (struct iter_forward_zone*)rbtree_search(fwd->tree, &key);
}
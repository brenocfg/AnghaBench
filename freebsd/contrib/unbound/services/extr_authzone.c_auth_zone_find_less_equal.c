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
struct auth_zones {int /*<<< orphan*/  ztree; } ;
struct TYPE_2__ {struct auth_zone* key; } ;
struct auth_zone {size_t namelen; int /*<<< orphan*/  namelabs; int /*<<< orphan*/ * name; int /*<<< orphan*/  dclass; TYPE_1__ node; } ;
typedef  int /*<<< orphan*/  rbnode_type ;

/* Variables and functions */
 int /*<<< orphan*/  dname_count_labels (int /*<<< orphan*/ *) ; 
 int rbtree_find_less_equal (int /*<<< orphan*/ *,struct auth_zone*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
auth_zone_find_less_equal(struct auth_zones* az, uint8_t* nm, size_t nmlen,
	uint16_t dclass, struct auth_zone** z)
{
	struct auth_zone key;
	key.node.key = &key;
	key.dclass = dclass;
	key.name = nm;
	key.namelen = nmlen;
	key.namelabs = dname_count_labels(nm);
	return rbtree_find_less_equal(&az->ztree, &key, (rbnode_type**)z);
}
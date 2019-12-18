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
struct local_zones {int /*<<< orphan*/  ztree; } ;
struct TYPE_2__ {struct local_zone* key; } ;
struct local_zone {size_t namelen; int namelabs; int /*<<< orphan*/ * name; int /*<<< orphan*/  dclass; TYPE_1__ node; } ;

/* Variables and functions */
 scalar_t__ rbtree_search (int /*<<< orphan*/ *,struct local_zone*) ; 

struct local_zone* 
local_zones_find(struct local_zones* zones,
        uint8_t* name, size_t len, int labs, uint16_t dclass)
{
	struct local_zone key;
	key.node.key = &key;
	key.dclass = dclass;
	key.name = name;
	key.namelen = len;
	key.namelabs = labs;
	/* exact */
	return (struct local_zone*)rbtree_search(&zones->ztree, &key);
}
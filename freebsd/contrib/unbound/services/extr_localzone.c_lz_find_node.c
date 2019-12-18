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
struct local_zone {int /*<<< orphan*/  data; } ;
struct TYPE_2__ {struct local_data* key; } ;
struct local_data {size_t namelen; int namelabs; TYPE_1__ node; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 scalar_t__ rbtree_search (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static struct local_data* 
lz_find_node(struct local_zone* z, uint8_t* nm, size_t nmlen, int nmlabs)
{
	struct local_data key;
	key.node.key = &key;
	key.name = nm;
	key.namelen = nmlen;
	key.namelabs = nmlabs;
	return (struct local_data*)rbtree_search(&z->data, &key.node);
}
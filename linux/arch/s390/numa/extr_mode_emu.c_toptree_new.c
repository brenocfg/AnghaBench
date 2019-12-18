#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct toptree {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TOPOLOGY ; 
 int /*<<< orphan*/  panic (char*) ; 
 struct toptree* toptree_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  toptree_get_child (struct toptree*,int) ; 

__attribute__((used)) static struct toptree *toptree_new(int id, int nodes)
{
	struct toptree *tree;
	int nid;

	tree = toptree_alloc(TOPOLOGY, id);
	if (!tree)
		goto fail;
	for (nid = 0; nid < nodes; nid++) {
		if (!toptree_get_child(tree, nid))
			goto fail;
	}
	return tree;
fail:
	panic("NUMA emulation could not allocate topology");
}
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
typedef  int /*<<< orphan*/  uint8_t ;
struct compress_tree_node {int labs; struct compress_tree_node* parent; } ;

/* Variables and functions */
 scalar_t__ compress_tree_search (struct compress_tree_node**,int /*<<< orphan*/ *,int,struct compress_tree_node**,int*,struct compress_tree_node***) ; 

__attribute__((used)) static struct compress_tree_node*
compress_tree_lookup(struct compress_tree_node** tree, uint8_t* dname,
	int labs, struct compress_tree_node*** insertpt)
{
	struct compress_tree_node* p;
	int m;
	if(labs <= 1)
		return 0; /* do not compress root node */
	if(compress_tree_search(tree, dname, labs, &p, &m, insertpt)) {
		/* exact match */
		return p;
	}
	/* return some ancestor of p that compresses well. */
	if(m>1) {
		/* www.example.com. (labs=4) matched foo.example.com.(labs=4)
		 * then matchcount = 3. need to go up. */
		while(p && p->labs > m)
			p = p->parent;
		return p;
	}
	return 0;
}
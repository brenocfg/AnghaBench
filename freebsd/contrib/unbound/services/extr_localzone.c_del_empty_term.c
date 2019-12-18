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
struct local_zone {int /*<<< orphan*/  data; } ;
struct local_data {int /*<<< orphan*/ * rrsets; } ;

/* Variables and functions */
 scalar_t__ dname_is_root (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dname_remove_label (int /*<<< orphan*/ **,size_t*) ; 
 scalar_t__ is_terminal (struct local_data*) ; 
 struct local_data* lz_find_node (struct local_zone*,int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  rbtree_delete (int /*<<< orphan*/ *,struct local_data*) ; 

__attribute__((used)) static void 
del_empty_term(struct local_zone* z, struct local_data* d, 
	uint8_t* name, size_t len, int labs)
{
	while(d && d->rrsets == NULL && is_terminal(d)) {
		/* is this empty nonterminal? delete */
		/* note, no memory recycling in zone region */
		(void)rbtree_delete(&z->data, d);

		/* go up and to the next label */
		if(dname_is_root(name))
			return;
		dname_remove_label(&name, &len);
		labs--;
		d = lz_find_node(z, name, len, labs);
	}
}
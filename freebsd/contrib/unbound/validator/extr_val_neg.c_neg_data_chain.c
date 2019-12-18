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
struct val_neg_data {int labs; struct val_neg_data* parent; struct val_neg_data* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dname_remove_label (int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  free (struct val_neg_data*) ; 
 struct val_neg_data* neg_setup_data_node (int /*<<< orphan*/ *,size_t,int) ; 

__attribute__((used)) static struct val_neg_data* neg_data_chain(
	uint8_t* nm, size_t nm_len, int labs, struct val_neg_data* parent)
{
	int i;
	int tolabs = parent?parent->labs:0;
	struct val_neg_data* el, *first = NULL, *prev = NULL;

	/* create the new subtree, i is labelcount of current creation */
	/* this creates a 'first' to z->parent=NULL list of zones */
	for(i=labs; i!=tolabs; i--) {
		/* create new item */
		el = neg_setup_data_node(nm, nm_len, i);
		if(!el) {
			/* need to delete other allocations in this routine!*/
			struct val_neg_data* p = first, *np;
			while(p) {
				np = p->parent;
				free(p->name);
				free(p);
				p = np;
			}
			return NULL;
		}
		if(i == labs) {
			first = el;
		} else {
			prev->parent = el;
		}

		/* prepare for next name */
		prev = el;
		dname_remove_label(&nm, &nm_len);
	}
	return first;
}
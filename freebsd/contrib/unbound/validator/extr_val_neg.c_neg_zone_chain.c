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
typedef  int /*<<< orphan*/  uint16_t ;
struct val_neg_zone {int labs; struct val_neg_zone* parent; struct val_neg_zone* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dname_remove_label (int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  free (struct val_neg_zone*) ; 
 struct val_neg_zone* neg_setup_zone_node (int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct val_neg_zone* neg_zone_chain(
	uint8_t* nm, size_t nm_len, int labs, uint16_t dclass,
	struct val_neg_zone* parent)
{
	int i;
	int tolabs = parent?parent->labs:0;
	struct val_neg_zone* zone, *prev = NULL, *first = NULL;

	/* create the new subtree, i is labelcount of current creation */
	/* this creates a 'first' to z->parent=NULL list of zones */
	for(i=labs; i!=tolabs; i--) {
		/* create new item */
		zone = neg_setup_zone_node(nm, nm_len, i, dclass);
		if(!zone) {
			/* need to delete other allocations in this routine!*/
			struct val_neg_zone* p=first, *np;
			while(p) {
				np = p->parent;
				free(p->name);
				free(p);
				p = np;
			}
			return NULL;
		}
		if(i == labs) {
			first = zone;
		} else {
			prev->parent = zone;
		}
		/* prepare for next name */
		prev = zone;
		dname_remove_label(&nm, &nm_len);
	}
	return first;
}
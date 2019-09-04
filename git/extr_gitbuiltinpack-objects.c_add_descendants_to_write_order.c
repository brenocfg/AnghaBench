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
struct object_entry {int dummy; } ;

/* Variables and functions */
 struct object_entry* DELTA (struct object_entry*) ; 
 struct object_entry* DELTA_CHILD (struct object_entry*) ; 
 struct object_entry* DELTA_SIBLING (struct object_entry*) ; 
 int /*<<< orphan*/  add_to_write_order (struct object_entry**,unsigned int*,struct object_entry*) ; 

__attribute__((used)) static void add_descendants_to_write_order(struct object_entry **wo,
					   unsigned int *endp,
					   struct object_entry *e)
{
	int add_to_order = 1;
	while (e) {
		if (add_to_order) {
			struct object_entry *s;
			/* add this node... */
			add_to_write_order(wo, endp, e);
			/* all its siblings... */
			for (s = DELTA_SIBLING(e); s; s = DELTA_SIBLING(s)) {
				add_to_write_order(wo, endp, s);
			}
		}
		/* drop down a level to add left subtree nodes if possible */
		if (DELTA_CHILD(e)) {
			add_to_order = 1;
			e = DELTA_CHILD(e);
		} else {
			add_to_order = 0;
			/* our sibling might have some children, it is next */
			if (DELTA_SIBLING(e)) {
				e = DELTA_SIBLING(e);
				continue;
			}
			/* go back to our parent node */
			e = DELTA(e);
			while (e && !DELTA_SIBLING(e)) {
				/* we're on the right side of a subtree, keep
				 * going up until we can go right again */
				e = DELTA(e);
			}
			if (!e) {
				/* done- we hit our original root node */
				return;
			}
			/* pass it off to sibling at this level */
			e = DELTA_SIBLING(e);
		}
	};
}
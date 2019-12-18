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
struct tree_desc_x {struct tree_desc_skip* skip; } ;
struct tree_desc_skip {struct tree_desc_skip* prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct tree_desc_skip*) ; 

__attribute__((used)) static void free_extended_entry(struct tree_desc_x *t)
{
	struct tree_desc_skip *p, *s;

	for (s = t->skip; s; s = p) {
		p = s->prev;
		free(s);
	}
}
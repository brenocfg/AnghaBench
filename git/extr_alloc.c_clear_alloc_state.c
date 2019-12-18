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
struct alloc_state {size_t slab_nr; int /*<<< orphan*/ * slabs; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

void clear_alloc_state(struct alloc_state *s)
{
	while (s->slab_nr > 0) {
		s->slab_nr--;
		free(s->slabs[s->slab_nr]);
	}

	FREE_AND_NULL(s->slabs);
}
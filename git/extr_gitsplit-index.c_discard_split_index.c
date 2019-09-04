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
struct split_index {struct split_index* base; scalar_t__ refcount; } ;
struct index_state {struct split_index* split_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  discard_index (struct split_index*) ; 
 int /*<<< orphan*/  free (struct split_index*) ; 

void discard_split_index(struct index_state *istate)
{
	struct split_index *si = istate->split_index;
	if (!si)
		return;
	istate->split_index = NULL;
	si->refcount--;
	if (si->refcount)
		return;
	if (si->base) {
		discard_index(si->base);
		free(si->base);
	}
	free(si);
}
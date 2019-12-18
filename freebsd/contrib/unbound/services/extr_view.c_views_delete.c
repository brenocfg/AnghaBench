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
struct views {int /*<<< orphan*/  vtree; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  delviewnode ; 
 int /*<<< orphan*/  free (struct views*) ; 
 int /*<<< orphan*/  lock_rw_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  traverse_postorder (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void 
views_delete(struct views* v)
{
	if(!v)
		return;
	lock_rw_destroy(&v->lock);
	traverse_postorder(&v->vtree, delviewnode, NULL);
	free(v);
}
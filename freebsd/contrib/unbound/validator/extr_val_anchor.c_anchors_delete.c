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
struct val_anchors {struct val_anchors* autr; struct val_anchors* tree; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  anchors_delfunc ; 
 int /*<<< orphan*/  autr_global_delete (struct val_anchors*) ; 
 int /*<<< orphan*/  free (struct val_anchors*) ; 
 int /*<<< orphan*/  lock_basic_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_unprotect (int /*<<< orphan*/ *,struct val_anchors*) ; 
 int /*<<< orphan*/  traverse_postorder (struct val_anchors*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void 
anchors_delete(struct val_anchors* anchors)
{
	if(!anchors)
		return;
	lock_unprotect(&anchors->lock, anchors->autr);
	lock_unprotect(&anchors->lock, anchors);
	lock_basic_destroy(&anchors->lock);
	if(anchors->tree)
		traverse_postorder(anchors->tree, anchors_delfunc, NULL);
	free(anchors->tree);
	autr_global_delete(anchors->autr);
	free(anchors);
}
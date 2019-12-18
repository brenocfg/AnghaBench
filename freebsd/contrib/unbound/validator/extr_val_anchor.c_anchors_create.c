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
struct val_anchors {struct val_anchors* autr; int /*<<< orphan*/  lock; int /*<<< orphan*/  tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  anchor_cmp ; 
 int /*<<< orphan*/  anchors_delete (struct val_anchors*) ; 
 struct val_anchors* autr_global_create () ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  lock_basic_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_protect (int /*<<< orphan*/ *,struct val_anchors*,int) ; 
 int /*<<< orphan*/  rbtree_create (int /*<<< orphan*/ ) ; 

struct val_anchors* 
anchors_create(void)
{
	struct val_anchors* a = (struct val_anchors*)calloc(1, sizeof(*a));
	if(!a)
		return NULL;
	a->tree = rbtree_create(anchor_cmp);
	if(!a->tree) {
		anchors_delete(a);
		return NULL;
	}
	a->autr = autr_global_create();
	if(!a->autr) {
		anchors_delete(a);
		return NULL;
	}
	lock_basic_init(&a->lock);
	lock_protect(&a->lock, a, sizeof(*a));
	lock_protect(&a->lock, a->autr, sizeof(*a->autr));
	return a;
}
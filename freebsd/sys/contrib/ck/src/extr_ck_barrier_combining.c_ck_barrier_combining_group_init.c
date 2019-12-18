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
struct ck_barrier_combining_queue {int /*<<< orphan*/ * head; int /*<<< orphan*/ * tail; } ;
struct ck_barrier_combining_group {unsigned int k; int /*<<< orphan*/ * right; int /*<<< orphan*/ * left; scalar_t__ sense; scalar_t__ count; } ;
struct ck_barrier_combining {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * root; } ;

/* Variables and functions */
 int /*<<< orphan*/  ck_barrier_combining_insert (struct ck_barrier_combining_group*,struct ck_barrier_combining_group*,int /*<<< orphan*/ **) ; 
 struct ck_barrier_combining_group* ck_barrier_combining_queue_dequeue (struct ck_barrier_combining_queue*) ; 
 int /*<<< orphan*/  ck_barrier_combining_queue_enqueue (struct ck_barrier_combining_queue*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ck_spinlock_fas_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ck_spinlock_fas_unlock (int /*<<< orphan*/ *) ; 

void
ck_barrier_combining_group_init(struct ck_barrier_combining *root,
    struct ck_barrier_combining_group *tnode,
    unsigned int nthr)
{
	struct ck_barrier_combining_group *node;
	struct ck_barrier_combining_queue queue;

	queue.head = queue.tail = NULL;

	tnode->k = nthr;
	tnode->count = 0;
	tnode->sense = 0;
	tnode->left = tnode->right = NULL;

	/*
	 * Finds the first available node for linkage into the combining
	 * tree. The use of a spinlock is excusable as this is a one-time
	 * initialization cost.
	 */
	ck_spinlock_fas_lock(&root->mutex);
	ck_barrier_combining_queue_enqueue(&queue, root->root);
	while (queue.head != NULL) {
		node = ck_barrier_combining_queue_dequeue(&queue);

		/* If the left child is free, link the group there. */
		if (node->left == NULL) {
			ck_barrier_combining_insert(node, tnode, &node->left);
			goto leave;
		}

		/* If the right child is free, link the group there. */
		if (node->right == NULL) {
			ck_barrier_combining_insert(node, tnode, &node->right);
			goto leave;
		}

		/*
		 * If unsuccessful, try inserting as a child of the children of the
		 * current node.
		 */
		ck_barrier_combining_queue_enqueue(&queue, node->left);
		ck_barrier_combining_queue_enqueue(&queue, node->right);
	}

leave:
	ck_spinlock_fas_unlock(&root->mutex);
	return;
}
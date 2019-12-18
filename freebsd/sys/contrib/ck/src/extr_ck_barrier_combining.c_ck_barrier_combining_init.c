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
struct ck_barrier_combining_group {int /*<<< orphan*/ * right; int /*<<< orphan*/  left; int /*<<< orphan*/  parent; scalar_t__ sense; scalar_t__ count; scalar_t__ k; } ;
struct ck_barrier_combining {struct ck_barrier_combining_group* root; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ck_spinlock_fas_init (int /*<<< orphan*/ *) ; 

void
ck_barrier_combining_init(struct ck_barrier_combining *root,
    struct ck_barrier_combining_group *init_root)
{

	init_root->k = 0;
	init_root->count = 0;
	init_root->sense = 0;
	init_root->parent = init_root->left = init_root->right = NULL;
	ck_spinlock_fas_init(&root->mutex);
	root->root = init_root;
	return;
}
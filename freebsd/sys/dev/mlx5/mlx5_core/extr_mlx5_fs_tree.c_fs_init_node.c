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
struct fs_base {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; int /*<<< orphan*/  complete; int /*<<< orphan*/  users_refcount; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fs_init_node(struct fs_base *node,
			 unsigned int refcount)
{
	kref_init(&node->refcount);
	atomic_set(&node->users_refcount, refcount);
	init_completion(&node->complete);
	INIT_LIST_HEAD(&node->list);
	mutex_init(&node->lock);
}
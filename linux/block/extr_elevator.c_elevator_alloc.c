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
struct request_queue {int /*<<< orphan*/  node; } ;
struct elevator_type {int dummy; } ;
struct elevator_queue {int /*<<< orphan*/  hash; int /*<<< orphan*/  sysfs_lock; int /*<<< orphan*/  kobj; struct elevator_type* type; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  elv_ktype ; 
 int /*<<< orphan*/  hash_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct elevator_queue* kzalloc_node (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

struct elevator_queue *elevator_alloc(struct request_queue *q,
				  struct elevator_type *e)
{
	struct elevator_queue *eq;

	eq = kzalloc_node(sizeof(*eq), GFP_KERNEL, q->node);
	if (unlikely(!eq))
		return NULL;

	eq->type = e;
	kobject_init(&eq->kobj, &elv_ktype);
	mutex_init(&eq->sysfs_lock);
	hash_init(eq->hash);

	return eq;
}
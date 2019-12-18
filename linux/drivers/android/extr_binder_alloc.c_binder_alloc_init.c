#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct binder_alloc {int /*<<< orphan*/  buffers; int /*<<< orphan*/  mutex; int /*<<< orphan*/  pid; } ;
struct TYPE_4__ {TYPE_1__* group_leader; } ;
struct TYPE_3__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void binder_alloc_init(struct binder_alloc *alloc)
{
	alloc->pid = current->group_leader->pid;
	mutex_init(&alloc->mutex);
	INIT_LIST_HEAD(&alloc->buffers);
}
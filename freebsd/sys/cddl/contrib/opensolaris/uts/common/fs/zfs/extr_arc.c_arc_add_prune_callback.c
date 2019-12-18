#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  p_refcnt; int /*<<< orphan*/  p_node; void* p_private; int /*<<< orphan*/ * p_pfunc; } ;
typedef  TYPE_1__ arc_prune_t ;
typedef  int /*<<< orphan*/  arc_prune_func_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  arc_prune_list ; 
 int /*<<< orphan*/  arc_prune_mtx ; 
 TYPE_1__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_insert_head (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  list_link_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_refcount_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_refcount_create (int /*<<< orphan*/ *) ; 

arc_prune_t *
arc_add_prune_callback(arc_prune_func_t *func, void *private)
{
	arc_prune_t *p;

	p = kmem_alloc(sizeof (*p), KM_SLEEP);
	p->p_pfunc = func;
	p->p_private = private;
	list_link_init(&p->p_node);
	zfs_refcount_create(&p->p_refcnt);

	mutex_enter(&arc_prune_mtx);
	zfs_refcount_add(&p->p_refcnt, &arc_prune_list);
	list_insert_head(&arc_prune_list, p);
	mutex_exit(&arc_prune_mtx);

	return (p);
}
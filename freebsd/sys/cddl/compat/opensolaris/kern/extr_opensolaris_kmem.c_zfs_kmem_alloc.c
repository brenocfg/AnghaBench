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
typedef  int /*<<< orphan*/  u_char ;
struct kmem_item {int /*<<< orphan*/  stack; } ;

/* Variables and functions */
 int KM_SLEEP ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct kmem_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_SOLARIS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_items ; 
 int /*<<< orphan*/  kmem_items_mtx ; 
 void* malloc (size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  stack_save (int /*<<< orphan*/ *) ; 

void *
zfs_kmem_alloc(size_t size, int kmflags)
{
	void *p;
#ifdef KMEM_DEBUG
	struct kmem_item *i;

	size += sizeof(struct kmem_item);
#endif
	p = malloc(size, M_SOLARIS, kmflags);
#ifndef _KERNEL
	if (kmflags & KM_SLEEP)
		assert(p != NULL);
#endif
#ifdef KMEM_DEBUG
	if (p != NULL) {
		i = p;
		p = (u_char *)p + sizeof(struct kmem_item);
		stack_save(&i->stack);
		mtx_lock(&kmem_items_mtx);
		LIST_INSERT_HEAD(&kmem_items, i, next);
		mtx_unlock(&kmem_items_mtx);
	}
#endif
	return (p);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  io_lock; int /*<<< orphan*/  io_parent_count; int /*<<< orphan*/  io_child_count; int /*<<< orphan*/  io_parent_list; int /*<<< orphan*/  io_child_list; } ;
typedef  TYPE_1__ zio_t ;
struct TYPE_9__ {TYPE_1__* zl_child; TYPE_1__* zl_parent; } ;
typedef  TYPE_2__ zio_link_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zio_link_cache ; 

__attribute__((used)) static void
zio_remove_child(zio_t *pio, zio_t *cio, zio_link_t *zl)
{
	ASSERT(zl->zl_parent == pio);
	ASSERT(zl->zl_child == cio);

	mutex_enter(&pio->io_lock);
	mutex_enter(&cio->io_lock);

	list_remove(&pio->io_child_list, zl);
	list_remove(&cio->io_parent_list, zl);

	pio->io_child_count--;
	cio->io_parent_count--;

	mutex_exit(&cio->io_lock);
	mutex_exit(&pio->io_lock);
	kmem_cache_free(zio_link_cache, zl);
}
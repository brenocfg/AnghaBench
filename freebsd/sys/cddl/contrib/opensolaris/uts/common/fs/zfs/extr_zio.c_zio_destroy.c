#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  io_cv; int /*<<< orphan*/  io_lock; int /*<<< orphan*/  io_child_list; int /*<<< orphan*/  io_parent_list; int /*<<< orphan*/  io_alloc_list; } ;
typedef  TYPE_1__ zio_t ;

/* Variables and functions */
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  list_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  metaslab_trace_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zio_cache ; 

__attribute__((used)) static void
zio_destroy(zio_t *zio)
{
	metaslab_trace_fini(&zio->io_alloc_list);
	list_destroy(&zio->io_parent_list);
	list_destroy(&zio->io_child_list);
	mutex_destroy(&zio->io_lock);
	cv_destroy(&zio->io_cv);
	kmem_cache_free(zio_cache, zio);
}
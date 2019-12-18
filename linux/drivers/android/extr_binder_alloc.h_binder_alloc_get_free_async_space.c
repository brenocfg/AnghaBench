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
struct binder_alloc {size_t free_async_space; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline size_t
binder_alloc_get_free_async_space(struct binder_alloc *alloc)
{
	size_t free_async_space;

	mutex_lock(&alloc->mutex);
	free_async_space = alloc->free_async_space;
	mutex_unlock(&alloc->mutex);
	return free_async_space;
}
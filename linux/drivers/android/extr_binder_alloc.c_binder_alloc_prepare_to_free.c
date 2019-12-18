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
struct binder_buffer {int dummy; } ;
struct binder_alloc {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 struct binder_buffer* binder_alloc_prepare_to_free_locked (struct binder_alloc*,uintptr_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct binder_buffer *binder_alloc_prepare_to_free(struct binder_alloc *alloc,
						   uintptr_t user_ptr)
{
	struct binder_buffer *buffer;

	mutex_lock(&alloc->mutex);
	buffer = binder_alloc_prepare_to_free_locked(alloc, user_ptr);
	mutex_unlock(&alloc->mutex);
	return buffer;
}
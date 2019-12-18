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
struct ttm_object_file {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 scalar_t__ refcount_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_object_file_destroy (struct ttm_object_file*) ; 

__attribute__((used)) static inline void ttm_object_file_unref(struct ttm_object_file **p_tfile)
{
	struct ttm_object_file *tfile = *p_tfile;

	*p_tfile = NULL;
	if (refcount_release(&tfile->refcount))
		ttm_object_file_destroy(tfile);
}
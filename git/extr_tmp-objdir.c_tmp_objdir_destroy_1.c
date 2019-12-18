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
struct tmp_objdir {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int remove_dir_recursively (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct tmp_objdir* the_tmp_objdir ; 
 int /*<<< orphan*/  tmp_objdir_free (struct tmp_objdir*) ; 

__attribute__((used)) static int tmp_objdir_destroy_1(struct tmp_objdir *t, int on_signal)
{
	int err;

	if (!t)
		return 0;

	if (t == the_tmp_objdir)
		the_tmp_objdir = NULL;

	/*
	 * This may use malloc via strbuf_grow(), but we should
	 * have pre-grown t->path sufficiently so that this
	 * doesn't happen in practice.
	 */
	err = remove_dir_recursively(&t->path, 0);

	/*
	 * When we are cleaning up due to a signal, we won't bother
	 * freeing memory; it may cause a deadlock if the signal
	 * arrived while libc's allocator lock is held.
	 */
	if (!on_signal)
		tmp_objdir_free(t);
	return err;
}
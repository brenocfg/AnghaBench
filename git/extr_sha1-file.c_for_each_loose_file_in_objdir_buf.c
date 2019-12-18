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
struct strbuf {int dummy; } ;
typedef  int /*<<< orphan*/  each_loose_subdir_fn ;
typedef  int /*<<< orphan*/  each_loose_object_fn ;
typedef  int /*<<< orphan*/  each_loose_cruft_fn ;

/* Variables and functions */
 int for_each_file_in_obj_subdir (int,struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

int for_each_loose_file_in_objdir_buf(struct strbuf *path,
			    each_loose_object_fn obj_cb,
			    each_loose_cruft_fn cruft_cb,
			    each_loose_subdir_fn subdir_cb,
			    void *data)
{
	int r = 0;
	int i;

	for (i = 0; i < 256; i++) {
		r = for_each_file_in_obj_subdir(i, path, obj_cb, cruft_cb,
						subdir_cb, data);
		if (r)
			break;
	}

	return r;
}
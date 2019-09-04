#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct index_state {int dummy; } ;
typedef  int /*<<< orphan*/  mmfile_t ;
struct TYPE_3__ {unsigned long size; void* ptr; } ;
typedef  TYPE_1__ mmbuffer_t ;

/* Variables and functions */
 int ll_merge (TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,struct index_state*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *three_way_filemerge(struct index_state *istate,
				 const char *path,
				 mmfile_t *base,
				 mmfile_t *our,
				 mmfile_t *their,
				 unsigned long *size)
{
	int merge_status;
	mmbuffer_t res;

	/*
	 * This function is only used by cmd_merge_tree, which
	 * does not respect the merge.conflictstyle option.
	 * There is no need to worry about a label for the
	 * common ancestor.
	 */
	merge_status = ll_merge(&res, path, base, NULL,
				our, ".our", their, ".their",
				istate, NULL);
	if (merge_status < 0)
		return NULL;

	*size = res.size;
	return res.ptr;
}
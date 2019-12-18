#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ll_merge_options {int variant; scalar_t__ virtual_ancestor; } ;
struct ll_merge_driver {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/ * ptr; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ mmfile_t ;
struct TYPE_8__ {int /*<<< orphan*/  size; int /*<<< orphan*/ * ptr; } ;
typedef  TYPE_2__ mmbuffer_t ;

/* Variables and functions */
#define  XDL_MERGE_FAVOR_OURS 129 
#define  XDL_MERGE_FAVOR_THEIRS 128 
 int /*<<< orphan*/  assert (struct ll_merge_options const*) ; 
 int /*<<< orphan*/  warning (char*,char const*,char const*,char const*) ; 

__attribute__((used)) static int ll_binary_merge(const struct ll_merge_driver *drv_unused,
			   mmbuffer_t *result,
			   const char *path,
			   mmfile_t *orig, const char *orig_name,
			   mmfile_t *src1, const char *name1,
			   mmfile_t *src2, const char *name2,
			   const struct ll_merge_options *opts,
			   int marker_size)
{
	mmfile_t *stolen;
	assert(opts);

	/*
	 * The tentative merge result is the common ancestor for an
	 * internal merge.  For the final merge, it is "ours" by
	 * default but -Xours/-Xtheirs can tweak the choice.
	 */
	if (opts->virtual_ancestor) {
		stolen = orig;
	} else {
		switch (opts->variant) {
		default:
			warning("Cannot merge binary files: %s (%s vs. %s)",
				path, name1, name2);
			/* fallthru */
		case XDL_MERGE_FAVOR_OURS:
			stolen = src1;
			break;
		case XDL_MERGE_FAVOR_THEIRS:
			stolen = src2;
			break;
		}
	}

	result->ptr = stolen->ptr;
	result->size = stolen->size;
	stolen->ptr = NULL;

	/*
	 * With -Xtheirs or -Xours, we have cleanly merged;
	 * otherwise we got a conflict.
	 */
	return (opts->variant ? 0 : 1);
}
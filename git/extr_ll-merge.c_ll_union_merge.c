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
struct ll_merge_options {int /*<<< orphan*/  variant; } ;
struct ll_merge_driver {int dummy; } ;
typedef  int /*<<< orphan*/  mmfile_t ;
typedef  int /*<<< orphan*/  mmbuffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  XDL_MERGE_FAVOR_UNION ; 
 int /*<<< orphan*/  assert (struct ll_merge_options const*) ; 
 int ll_xdl_merge (struct ll_merge_driver const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ll_merge_options*,int) ; 

__attribute__((used)) static int ll_union_merge(const struct ll_merge_driver *drv_unused,
			  mmbuffer_t *result,
			  const char *path_unused,
			  mmfile_t *orig, const char *orig_name,
			  mmfile_t *src1, const char *name1,
			  mmfile_t *src2, const char *name2,
			  const struct ll_merge_options *opts,
			  int marker_size)
{
	/* Use union favor */
	struct ll_merge_options o;
	assert(opts);
	o = *opts;
	o.variant = XDL_MERGE_FAVOR_UNION;
	return ll_xdl_merge(drv_unused, result, path_unused,
			    orig, NULL, src1, NULL, src2, NULL,
			    &o, marker_size);
}
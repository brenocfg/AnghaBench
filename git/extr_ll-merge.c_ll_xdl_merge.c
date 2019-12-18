#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  flags; } ;
struct TYPE_16__ {int marker_size; char const* ancestor; char const* file1; char const* file2; scalar_t__ style; TYPE_1__ xpp; int /*<<< orphan*/  favor; int /*<<< orphan*/  level; } ;
typedef  TYPE_2__ xmparam_t ;
typedef  int /*<<< orphan*/  xmp ;
struct ll_merge_options {int /*<<< orphan*/  xdl_opts; int /*<<< orphan*/  variant; } ;
struct ll_merge_driver {int dummy; } ;
struct TYPE_17__ {scalar_t__ size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_3__ mmfile_t ;
typedef  int /*<<< orphan*/  mmbuffer_t ;

/* Variables and functions */
 scalar_t__ MAX_XDIFF_SIZE ; 
 int /*<<< orphan*/  XDL_MERGE_ZEALOUS ; 
 int /*<<< orphan*/  assert (struct ll_merge_options const*) ; 
 scalar_t__ buffer_is_binary (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ git_xmerge_style ; 
 int ll_binary_merge (struct ll_merge_driver const*,int /*<<< orphan*/ *,char const*,TYPE_3__*,char const*,TYPE_3__*,char const*,TYPE_3__*,char const*,struct ll_merge_options const*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int xdl_merge (TYPE_3__*,TYPE_3__*,TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ll_xdl_merge(const struct ll_merge_driver *drv_unused,
			mmbuffer_t *result,
			const char *path,
			mmfile_t *orig, const char *orig_name,
			mmfile_t *src1, const char *name1,
			mmfile_t *src2, const char *name2,
			const struct ll_merge_options *opts,
			int marker_size)
{
	xmparam_t xmp;
	assert(opts);

	if (orig->size > MAX_XDIFF_SIZE ||
	    src1->size > MAX_XDIFF_SIZE ||
	    src2->size > MAX_XDIFF_SIZE ||
	    buffer_is_binary(orig->ptr, orig->size) ||
	    buffer_is_binary(src1->ptr, src1->size) ||
	    buffer_is_binary(src2->ptr, src2->size)) {
		return ll_binary_merge(drv_unused, result,
				       path,
				       orig, orig_name,
				       src1, name1,
				       src2, name2,
				       opts, marker_size);
	}

	memset(&xmp, 0, sizeof(xmp));
	xmp.level = XDL_MERGE_ZEALOUS;
	xmp.favor = opts->variant;
	xmp.xpp.flags = opts->xdl_opts;
	if (git_xmerge_style >= 0)
		xmp.style = git_xmerge_style;
	if (marker_size > 0)
		xmp.marker_size = marker_size;
	xmp.ancestor = orig_name;
	xmp.file1 = name1;
	xmp.file2 = name2;
	return xdl_merge(orig, src1, src2, &xmp, result);
}
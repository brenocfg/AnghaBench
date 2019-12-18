#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct merge_options {int recursive_variant; char const* ancestor; TYPE_2__* repo; TYPE_1__* priv; int /*<<< orphan*/  xdl_opts; int /*<<< orphan*/  renormalize; } ;
struct ll_merge_options {int extra_marker_size; int virtual_ancestor; scalar_t__ variant; int /*<<< orphan*/  xdl_opts; int /*<<< orphan*/  renormalize; int /*<<< orphan*/  member_0; } ;
struct diff_filespec {scalar_t__ path; int /*<<< orphan*/  oid; } ;
struct TYPE_10__ {char* ptr; } ;
typedef  TYPE_3__ mmfile_t ;
typedef  int /*<<< orphan*/  mmbuffer_t ;
struct TYPE_9__ {int /*<<< orphan*/  index; } ;
struct TYPE_8__ {scalar_t__ call_depth; } ;

/* Variables and functions */
#define  MERGE_VARIANT_OURS 129 
#define  MERGE_VARIANT_THEIRS 128 
 scalar_t__ XDL_MERGE_FAVOR_OURS ; 
 scalar_t__ XDL_MERGE_FAVOR_THEIRS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int ll_merge (int /*<<< orphan*/ *,scalar_t__,TYPE_3__*,char*,TYPE_3__*,char*,TYPE_3__*,char*,int /*<<< orphan*/ ,struct ll_merge_options*) ; 
 char* mkpathdup (char*,char const*,...) ; 
 int /*<<< orphan*/  read_mmblob (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int merge_3way(struct merge_options *opt,
		      mmbuffer_t *result_buf,
		      const struct diff_filespec *o,
		      const struct diff_filespec *a,
		      const struct diff_filespec *b,
		      const char *branch1,
		      const char *branch2,
		      const int extra_marker_size)
{
	mmfile_t orig, src1, src2;
	struct ll_merge_options ll_opts = {0};
	char *base, *name1, *name2;
	int merge_status;

	ll_opts.renormalize = opt->renormalize;
	ll_opts.extra_marker_size = extra_marker_size;
	ll_opts.xdl_opts = opt->xdl_opts;

	if (opt->priv->call_depth) {
		ll_opts.virtual_ancestor = 1;
		ll_opts.variant = 0;
	} else {
		switch (opt->recursive_variant) {
		case MERGE_VARIANT_OURS:
			ll_opts.variant = XDL_MERGE_FAVOR_OURS;
			break;
		case MERGE_VARIANT_THEIRS:
			ll_opts.variant = XDL_MERGE_FAVOR_THEIRS;
			break;
		default:
			ll_opts.variant = 0;
			break;
		}
	}

	assert(a->path && b->path && o->path && opt->ancestor);
	if (strcmp(a->path, b->path) || strcmp(a->path, o->path) != 0) {
		base  = mkpathdup("%s:%s", opt->ancestor, o->path);
		name1 = mkpathdup("%s:%s", branch1, a->path);
		name2 = mkpathdup("%s:%s", branch2, b->path);
	} else {
		base  = mkpathdup("%s", opt->ancestor);
		name1 = mkpathdup("%s", branch1);
		name2 = mkpathdup("%s", branch2);
	}

	read_mmblob(&orig, &o->oid);
	read_mmblob(&src1, &a->oid);
	read_mmblob(&src2, &b->oid);

	merge_status = ll_merge(result_buf, a->path, &orig, base,
				&src1, name1, &src2, name2,
				opt->repo->index, &ll_opts);

	free(base);
	free(name1);
	free(name2);
	free(orig.ptr);
	free(src1.ptr);
	free(src2.ptr);
	return merge_status;
}
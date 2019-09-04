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
struct merge_options {int recursive_variant; char const* ancestor; TYPE_1__* repo; scalar_t__ call_depth; int /*<<< orphan*/  xdl_opts; int /*<<< orphan*/  renormalize; } ;
struct ll_merge_options {int extra_marker_size; int virtual_ancestor; scalar_t__ variant; int /*<<< orphan*/  xdl_opts; int /*<<< orphan*/  renormalize; int /*<<< orphan*/  member_0; } ;
struct diff_filespec {int /*<<< orphan*/  path; int /*<<< orphan*/  oid; } ;
struct TYPE_8__ {char* ptr; } ;
typedef  TYPE_2__ mmfile_t ;
typedef  int /*<<< orphan*/  mmbuffer_t ;
struct TYPE_7__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
#define  MERGE_RECURSIVE_OURS 129 
#define  MERGE_RECURSIVE_THEIRS 128 
 scalar_t__ XDL_MERGE_FAVOR_OURS ; 
 scalar_t__ XDL_MERGE_FAVOR_THEIRS ; 
 int /*<<< orphan*/  free (char*) ; 
 int ll_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,char*,TYPE_2__*,char*,TYPE_2__*,char*,int /*<<< orphan*/ ,struct ll_merge_options*) ; 
 char* mkpathdup (char*,char const*,...) ; 
 int /*<<< orphan*/  read_mmblob (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int merge_3way(struct merge_options *o,
		      mmbuffer_t *result_buf,
		      const struct diff_filespec *one,
		      const struct diff_filespec *a,
		      const struct diff_filespec *b,
		      const char *branch1,
		      const char *branch2,
		      const int extra_marker_size)
{
	mmfile_t orig, src1, src2;
	struct ll_merge_options ll_opts = {0};
	char *base_name, *name1, *name2;
	int merge_status;

	ll_opts.renormalize = o->renormalize;
	ll_opts.extra_marker_size = extra_marker_size;
	ll_opts.xdl_opts = o->xdl_opts;

	if (o->call_depth) {
		ll_opts.virtual_ancestor = 1;
		ll_opts.variant = 0;
	} else {
		switch (o->recursive_variant) {
		case MERGE_RECURSIVE_OURS:
			ll_opts.variant = XDL_MERGE_FAVOR_OURS;
			break;
		case MERGE_RECURSIVE_THEIRS:
			ll_opts.variant = XDL_MERGE_FAVOR_THEIRS;
			break;
		default:
			ll_opts.variant = 0;
			break;
		}
	}

	if (strcmp(a->path, b->path) ||
	    (o->ancestor != NULL && strcmp(a->path, one->path) != 0)) {
		base_name = o->ancestor == NULL ? NULL :
			mkpathdup("%s:%s", o->ancestor, one->path);
		name1 = mkpathdup("%s:%s", branch1, a->path);
		name2 = mkpathdup("%s:%s", branch2, b->path);
	} else {
		base_name = o->ancestor == NULL ? NULL :
			mkpathdup("%s", o->ancestor);
		name1 = mkpathdup("%s", branch1);
		name2 = mkpathdup("%s", branch2);
	}

	read_mmblob(&orig, &one->oid);
	read_mmblob(&src1, &a->oid);
	read_mmblob(&src2, &b->oid);

	merge_status = ll_merge(result_buf, a->path, &orig, base_name,
				&src1, name1, &src2, name2,
				o->repo->index, &ll_opts);

	free(base_name);
	free(name1);
	free(name2);
	free(orig.ptr);
	free(src1.ptr);
	free(src2.ptr);
	return merge_status;
}
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
struct merge_options {char const* branch1; int recursive_variant; } ;
struct merge_file_info {int merge; int clean; int mode; int /*<<< orphan*/  oid; } ;
struct diff_filespec {int mode; int /*<<< orphan*/  oid; int /*<<< orphan*/  path; } ;
struct TYPE_3__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ mmbuffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
#define  MERGE_RECURSIVE_NORMAL 130 
#define  MERGE_RECURSIVE_OURS 129 
#define  MERGE_RECURSIVE_THEIRS 128 
 int S_IFMT ; 
 scalar_t__ S_ISGITLINK (int) ; 
 scalar_t__ S_ISLNK (int) ; 
 scalar_t__ S_ISREG (int) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  blob_type ; 
 int err (struct merge_options*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int merge_3way (struct merge_options*,TYPE_1__*,struct diff_filespec const*,struct diff_filespec const*,struct diff_filespec const*,char const*,char const*,int const) ; 
 int merge_submodule (struct merge_options*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ oid_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  output (struct merge_options*,int,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ write_object_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int merge_mode_and_contents(struct merge_options *o,
				   const struct diff_filespec *one,
				   const struct diff_filespec *a,
				   const struct diff_filespec *b,
				   const char *filename,
				   const char *branch1,
				   const char *branch2,
				   const int extra_marker_size,
				   struct merge_file_info *result)
{
	if (o->branch1 != branch1) {
		/*
		 * It's weird getting a reverse merge with HEAD on the bottom
		 * side of the conflict markers and the other branch on the
		 * top.  Fix that.
		 */
		return merge_mode_and_contents(o, one, b, a,
					       filename,
					       branch2, branch1,
					       extra_marker_size, result);
	}

	result->merge = 0;
	result->clean = 1;

	if ((S_IFMT & a->mode) != (S_IFMT & b->mode)) {
		result->clean = 0;
		if (S_ISREG(a->mode)) {
			result->mode = a->mode;
			oidcpy(&result->oid, &a->oid);
		} else {
			result->mode = b->mode;
			oidcpy(&result->oid, &b->oid);
		}
	} else {
		if (!oid_eq(&a->oid, &one->oid) && !oid_eq(&b->oid, &one->oid))
			result->merge = 1;

		/*
		 * Merge modes
		 */
		if (a->mode == b->mode || a->mode == one->mode)
			result->mode = b->mode;
		else {
			result->mode = a->mode;
			if (b->mode != one->mode) {
				result->clean = 0;
				result->merge = 1;
			}
		}

		if (oid_eq(&a->oid, &b->oid) || oid_eq(&a->oid, &one->oid))
			oidcpy(&result->oid, &b->oid);
		else if (oid_eq(&b->oid, &one->oid))
			oidcpy(&result->oid, &a->oid);
		else if (S_ISREG(a->mode)) {
			mmbuffer_t result_buf;
			int ret = 0, merge_status;

			merge_status = merge_3way(o, &result_buf, one, a, b,
						  branch1, branch2,
						  extra_marker_size);

			if ((merge_status < 0) || !result_buf.ptr)
				ret = err(o, _("Failed to execute internal merge"));

			if (!ret &&
			    write_object_file(result_buf.ptr, result_buf.size,
					      blob_type, &result->oid))
				ret = err(o, _("Unable to add %s to database"),
					  a->path);

			free(result_buf.ptr);
			if (ret)
				return ret;
			result->clean = (merge_status == 0);
		} else if (S_ISGITLINK(a->mode)) {
			result->clean = merge_submodule(o, &result->oid,
							one->path,
							&one->oid,
							&a->oid,
							&b->oid);
		} else if (S_ISLNK(a->mode)) {
			switch (o->recursive_variant) {
			case MERGE_RECURSIVE_NORMAL:
				oidcpy(&result->oid, &a->oid);
				if (!oid_eq(&a->oid, &b->oid))
					result->clean = 0;
				break;
			case MERGE_RECURSIVE_OURS:
				oidcpy(&result->oid, &a->oid);
				break;
			case MERGE_RECURSIVE_THEIRS:
				oidcpy(&result->oid, &b->oid);
				break;
			}
		} else
			BUG("unsupported object type in the tree");
	}

	if (result->merge)
		output(o, 2, _("Auto-merging %s"), filename);

	return 0;
}
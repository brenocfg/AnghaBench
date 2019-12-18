#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_25__ {int /*<<< orphan*/  payload; int /*<<< orphan*/  (* binary_cb ) (int /*<<< orphan*/ ,TYPE_11__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_9__ git_patch_generated_output ;
struct TYPE_21__ {int flags; } ;
struct TYPE_22__ {int /*<<< orphan*/  delta; TYPE_5__ diff_opts; } ;
struct TYPE_19__ {char* data; size_t len; } ;
struct TYPE_20__ {TYPE_3__ map; } ;
struct TYPE_17__ {char* data; size_t len; } ;
struct TYPE_18__ {TYPE_1__ map; } ;
struct TYPE_15__ {TYPE_6__ base; TYPE_4__ nfile; TYPE_2__ ofile; } ;
typedef  TYPE_10__ git_patch_generated ;
struct TYPE_24__ {scalar_t__ data; int /*<<< orphan*/  inflatedlen; int /*<<< orphan*/  datalen; int /*<<< orphan*/  type; } ;
struct TYPE_23__ {scalar_t__ data; int /*<<< orphan*/  inflatedlen; int /*<<< orphan*/  datalen; int /*<<< orphan*/  type; } ;
struct TYPE_16__ {int contains_data; TYPE_8__ new_file; TYPE_7__ old_file; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_11__ git_diff_binary ;

/* Variables and functions */
 int GIT_DIFF_SHOW_BINARY ; 
 int create_binary (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,size_t,char const*,size_t) ; 
 int /*<<< orphan*/  git__free (char*) ; 
 int git_error_set_after_callback_function (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_11__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int diff_binary(git_patch_generated_output *output, git_patch_generated *patch)
{
	git_diff_binary binary = {0};
	const char *old_data = patch->ofile.map.data;
	const char *new_data = patch->nfile.map.data;
	size_t old_len = patch->ofile.map.len,
		new_len = patch->nfile.map.len;
	int error;

	/* Only load contents if the user actually wants to diff
	 * binary files. */
	if (patch->base.diff_opts.flags & GIT_DIFF_SHOW_BINARY) {
		binary.contains_data = 1;

		/* Create the old->new delta (as the "new" side of the patch),
		 * and the new->old delta (as the "old" side)
		 */
		if ((error = create_binary(&binary.old_file.type,
				(char **)&binary.old_file.data,
				&binary.old_file.datalen,
				&binary.old_file.inflatedlen,
				new_data, new_len, old_data, old_len)) < 0 ||
			(error = create_binary(&binary.new_file.type,
				(char **)&binary.new_file.data,
				&binary.new_file.datalen,
				&binary.new_file.inflatedlen,
				old_data, old_len, new_data, new_len)) < 0)
			return error;
	}

	error = git_error_set_after_callback_function(
		output->binary_cb(patch->base.delta, &binary, output->payload),
		"git_patch");

	git__free((char *) binary.old_file.data);
	git__free((char *) binary.new_file.data);

	return error;
}
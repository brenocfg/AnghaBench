#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xo ;
struct TYPE_13__ {int /*<<< orphan*/  patch; } ;
typedef  TYPE_1__ patch_generated_with_delta ;
struct TYPE_14__ {int /*<<< orphan*/  output; } ;
typedef  TYPE_2__ git_xdiff_output ;
typedef  int /*<<< orphan*/  git_patch ;
typedef  int /*<<< orphan*/  git_diff_options ;
struct TYPE_15__ {int /*<<< orphan*/  as_path; } ;
typedef  TYPE_3__ git_diff_file_content_src ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  diff_output_to_patch (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_xdiff_init (TYPE_2__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int patch_generated_from_sources (TYPE_1__*,TYPE_2__*,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/  const*) ; 
 int patch_generated_with_delta_alloc (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int patch_from_sources(
	git_patch **out,
	git_diff_file_content_src *oldsrc,
	git_diff_file_content_src *newsrc,
	const git_diff_options *opts)
{
	int error = 0;
	patch_generated_with_delta *pd;
	git_xdiff_output xo;

	assert(out);
	*out = NULL;

	if ((error = patch_generated_with_delta_alloc(
			&pd, &oldsrc->as_path, &newsrc->as_path)) < 0)
		return error;

	memset(&xo, 0, sizeof(xo));
	diff_output_to_patch(&xo.output, &pd->patch);
	git_xdiff_init(&xo, opts);

	if (!(error = patch_generated_from_sources(pd, &xo, oldsrc, newsrc, opts)))
		*out = (git_patch *)pd;
	else
		git_patch_free((git_patch *)pd);

	return error;
}
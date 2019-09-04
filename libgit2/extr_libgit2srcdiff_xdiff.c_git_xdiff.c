#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  info ;
struct TYPE_9__ {int error; } ;
struct TYPE_15__ {TYPE_3__* priv; } ;
struct TYPE_14__ {int /*<<< orphan*/  flags; int /*<<< orphan*/ * find_func; int /*<<< orphan*/ * find_func_priv; } ;
struct TYPE_10__ {TYPE_1__ output; TYPE_7__ callback; TYPE_6__ config; int /*<<< orphan*/  params; } ;
typedef  TYPE_2__ git_xdiff_output ;
struct TYPE_13__ {scalar_t__ size; int /*<<< orphan*/  ptr; } ;
struct TYPE_12__ {scalar_t__ size; int /*<<< orphan*/  ptr; } ;
struct TYPE_11__ {TYPE_5__ xd_new_data; TYPE_4__ xd_old_data; TYPE_2__* xo; int /*<<< orphan*/ * patch; } ;
typedef  TYPE_3__ git_xdiff_info ;
typedef  int /*<<< orphan*/  git_patch_generated_output ;
typedef  int /*<<< orphan*/  git_patch_generated ;
typedef  int /*<<< orphan*/  git_diff_find_context_payload ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 scalar_t__ GIT_XDIFF_MAX_SIZE ; 
 int /*<<< orphan*/  XDL_EMIT_FUNCNAMES ; 
 int /*<<< orphan*/  git_diff_find_context_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_find_context_init (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_patch_generated_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_generated_new_data (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_generated_old_data (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xdl_diff (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ *,TYPE_6__*,TYPE_7__*) ; 

__attribute__((used)) static int git_xdiff(git_patch_generated_output *output, git_patch_generated *patch)
{
	git_xdiff_output *xo = (git_xdiff_output *)output;
	git_xdiff_info info;
	git_diff_find_context_payload findctxt;

	memset(&info, 0, sizeof(info));
	info.patch = patch;
	info.xo    = xo;

	xo->callback.priv = &info;

	git_diff_find_context_init(
		&xo->config.find_func, &findctxt, git_patch_generated_driver(patch));
	xo->config.find_func_priv = &findctxt;

	if (xo->config.find_func != NULL)
		xo->config.flags |= XDL_EMIT_FUNCNAMES;
	else
		xo->config.flags &= ~XDL_EMIT_FUNCNAMES;

	/* TODO: check ofile.opts_flags to see if driver-specific per-file
	 * updates are needed to xo->params.flags
	 */

	git_patch_generated_old_data(&info.xd_old_data.ptr, &info.xd_old_data.size, patch);
	git_patch_generated_new_data(&info.xd_new_data.ptr, &info.xd_new_data.size, patch);

	if (info.xd_old_data.size > GIT_XDIFF_MAX_SIZE ||
		info.xd_new_data.size > GIT_XDIFF_MAX_SIZE) {
		git_error_set(GIT_ERROR_INVALID, "files too large for diff");
		return -1;
	}

	xdl_diff(&info.xd_old_data, &info.xd_new_data,
		&xo->params, &xo->config, &xo->callback);

	git_diff_find_context_clear(&findctxt);

	return xo->output.error;
}
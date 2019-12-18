#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_9__ {int /*<<< orphan*/  session_relpath; int /*<<< orphan*/  orig_path_2; int /*<<< orphan*/  orig_path_1; int /*<<< orphan*/  anchor; } ;
struct TYPE_10__ {int /*<<< orphan*/  wc_ctx; int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; TYPE_1__ ddi; int /*<<< orphan*/  use_git_diff_format; int /*<<< orphan*/  relative_to_dir; int /*<<< orphan*/  outstream; int /*<<< orphan*/  header_encoding; scalar_t__ ignore_properties; } ;
typedef  TYPE_2__ diff_writer_info_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_11__ {scalar_t__ nelts; } ;
typedef  TYPE_3__ apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  display_prop_diffs (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_categorize_props (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
diff_props_changed(const char *diff_relpath,
                   svn_revnum_t rev1,
                   svn_revnum_t rev2,
                   const apr_array_header_t *propchanges,
                   apr_hash_t *left_props,
                   apr_hash_t *right_props,
                   svn_boolean_t show_diff_header,
                   diff_writer_info_t *dwi,
                   apr_pool_t *scratch_pool)
{
  apr_array_header_t *props;

  /* If property differences are ignored, there's nothing to do. */
  if (dwi->ignore_properties)
    return SVN_NO_ERROR;

  SVN_ERR(svn_categorize_props(propchanges, NULL, NULL, &props,
                               scratch_pool));

  if (props->nelts > 0)
    {
      /* We're using the revnums from the dwi since there's
       * no revision argument to the svn_wc_diff_callback_t
       * dir_props_changed(). */
      SVN_ERR(display_prop_diffs(props, left_props, right_props,
                                 diff_relpath,
                                 dwi->ddi.anchor,
                                 dwi->ddi.orig_path_1,
                                 dwi->ddi.orig_path_2,
                                 rev1,
                                 rev2,
                                 dwi->header_encoding,
                                 dwi->outstream,
                                 dwi->relative_to_dir,
                                 show_diff_header,
                                 dwi->use_git_diff_format,
                                 dwi->ddi.session_relpath,
                                 dwi->cancel_func,
                                 dwi->cancel_baton,
                                 dwi->wc_ctx,
                                 scratch_pool));
    }

  return SVN_NO_ERROR;
}
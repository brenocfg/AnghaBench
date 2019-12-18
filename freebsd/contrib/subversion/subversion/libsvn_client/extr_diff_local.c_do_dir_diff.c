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
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_15__ {int /*<<< orphan*/  (* dir_added ) (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,TYPE_1__ const*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* dir_deleted ) (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,TYPE_1__ const*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* dir_closed ) (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,TYPE_1__ const*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* dir_changed ) (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,void*,TYPE_1__ const*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* dir_opened ) (void**,scalar_t__*,scalar_t__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ svn_diff_tree_processor_t ;
typedef  int /*<<< orphan*/  svn_diff_source_t ;
typedef  scalar_t__ svn_depth_t ;
struct TYPE_16__ {int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_2__ svn_client_ctx_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_17__ {scalar_t__ nelts; } ;
typedef  TYPE_3__ apr_array_header_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_props (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inner_dir_diff (char const*,char const*,char const*,char const*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,void*,TYPE_1__ const*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (void**,scalar_t__*,scalar_t__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,void*,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_depth_files ; 
 int /*<<< orphan*/ * svn_diff__source_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* svn_dirent_skip_ancestor (char const*,char const*) ; 
 int /*<<< orphan*/  svn_prop_diffs (TYPE_3__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
do_dir_diff(const char *left_abspath,
            const char *right_abspath,
            const char *left_root_abspath,
            const char *right_root_abspath,
            svn_boolean_t left_only,
            svn_boolean_t right_only,
            svn_boolean_t left_before_right,
            svn_depth_t depth,
            void *parent_baton,
            const svn_diff_tree_processor_t *diff_processor,
            svn_client_ctx_t *ctx,
            apr_pool_t *scratch_pool)
{
  const char *relpath;
  svn_diff_source_t *left_source;
  svn_diff_source_t *right_source;
  svn_boolean_t skip = FALSE;
  svn_boolean_t skip_children = FALSE;
  void *dir_baton;
  apr_hash_t *left_props;
  apr_hash_t *right_props;

  relpath = svn_dirent_skip_ancestor(left_root_abspath, left_abspath);

  if (! right_only)
    {
      left_source = svn_diff__source_create(SVN_INVALID_REVNUM, scratch_pool);
      SVN_ERR(get_props(&left_props, left_abspath, ctx->wc_ctx,
                        scratch_pool, scratch_pool));
    }
  else
    {
      left_source = NULL;
      left_props = NULL;
    }

  if (! left_only)
    {
      right_source = svn_diff__source_create(SVN_INVALID_REVNUM, scratch_pool);
      SVN_ERR(get_props(&right_props, right_abspath, ctx->wc_ctx,
                        scratch_pool, scratch_pool));
    }
  else
    {
      right_source = NULL;
      right_props = NULL;
    }

  SVN_ERR(diff_processor->dir_opened(&dir_baton, &skip, &skip_children,
                                     relpath,
                                     left_source,
                                     right_source,
                                     NULL /* copyfrom_source */,
                                     parent_baton,
                                     diff_processor,
                                     scratch_pool, scratch_pool));

  if (!skip_children)
    {
      if (depth >= svn_depth_files)
        SVN_ERR(inner_dir_diff(left_abspath, right_abspath,
                               left_root_abspath, right_root_abspath,
                               left_only, right_only,
                               left_before_right, depth,
                               dir_baton,
                               diff_processor, ctx, scratch_pool));
    }
  else if (skip)
    return SVN_NO_ERROR;

  if (left_props && right_props)
    {
      apr_array_header_t *prop_diffs;

      SVN_ERR(svn_prop_diffs(&prop_diffs, right_props, left_props,
                             scratch_pool));

      if (prop_diffs->nelts)
        {
          SVN_ERR(diff_processor->dir_changed(relpath,
                                              left_source,
                                              right_source,
                                              left_props,
                                              right_props,
                                              prop_diffs,
                                              dir_baton,
                                              diff_processor,
                                              scratch_pool));
          return SVN_NO_ERROR;
        }
    }

  if (left_source && right_source)
    {
      SVN_ERR(diff_processor->dir_closed(relpath,
                                         left_source,
                                         right_source,
                                         dir_baton,
                                         diff_processor,
                                         scratch_pool));
    }
  else if (left_source)
    {
      SVN_ERR(diff_processor->dir_deleted(relpath,
                                          left_source,
                                          left_props,
                                          dir_baton,
                                          diff_processor,
                                          scratch_pool));
    }
  else
    {
      SVN_ERR(diff_processor->dir_added(relpath,
                                        NULL /* copyfrom_source */,
                                        right_source,
                                        NULL /* copyfrom_props */,
                                        right_props,
                                        dir_baton,
                                        diff_processor,
                                        scratch_pool));
    }

  return SVN_NO_ERROR;
}
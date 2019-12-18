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
struct TYPE_13__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ svn_wc_context_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_14__ {int /*<<< orphan*/  (* dir_closed ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__ const*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* dir_changed ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,TYPE_2__ const*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ svn_diff_tree_processor_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int svn_boolean_t ;
struct node_state_t {int /*<<< orphan*/  pool; struct node_state_t* parent; int /*<<< orphan*/  baton; int /*<<< orphan*/  right_src; int /*<<< orphan*/  left_src; int /*<<< orphan*/  relpath; scalar_t__ propchanges; int /*<<< orphan*/  right_props; int /*<<< orphan*/  left_props; int /*<<< orphan*/  skip; } ;
struct diff_baton {char const* anchor_abspath; int ignore_ancestry; struct node_state_t* cur; int /*<<< orphan*/ * pool; TYPE_2__ const* processor; int /*<<< orphan*/  db; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_15__ {scalar_t__ nelts; } ;
typedef  TYPE_3__ apr_array_header_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int TRUE ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diff_status_callback ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,TYPE_2__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__ const*,int /*<<< orphan*/ ) ; 
 void* svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/  svn_dirent_skip_ancestor (char const*,char const*) ; 
 int /*<<< orphan*/  svn_hash_from_cstring_keys (int /*<<< orphan*/ **,TYPE_3__ const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_wc__changelist_filter_tree_processor_create (TYPE_2__ const*,TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_is_wcroot (int*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_kind (scalar_t__*,int /*<<< orphan*/ ,char const*,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__internal_walk_status (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct diff_baton*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__diff7(const char **root_relpath,
              svn_boolean_t *root_is_dir,
              svn_wc_context_t *wc_ctx,
              const char *local_abspath,
              svn_depth_t depth,
              svn_boolean_t ignore_ancestry,
              const apr_array_header_t *changelist_filter,
              const svn_diff_tree_processor_t *diff_processor,
              svn_cancel_func_t cancel_func,
              void *cancel_baton,
              apr_pool_t *result_pool,
              apr_pool_t *scratch_pool)
{
  struct diff_baton eb = { 0 };
  svn_node_kind_t kind;
  svn_boolean_t get_all;

  SVN_ERR_ASSERT(svn_dirent_is_absolute(local_abspath));
  SVN_ERR(svn_wc__db_read_kind(&kind, wc_ctx->db, local_abspath,
                               FALSE /* allow_missing */,
                               TRUE /* show_deleted */,
                               FALSE /* show_hidden */,
                               scratch_pool));

  eb.anchor_abspath = local_abspath;

  if (root_relpath)
    {
      svn_boolean_t is_wcroot;

      SVN_ERR(svn_wc__db_is_wcroot(&is_wcroot,
                                   wc_ctx->db, local_abspath, scratch_pool));

      if (!is_wcroot)
        eb.anchor_abspath = svn_dirent_dirname(local_abspath, scratch_pool);
    }
  else if (kind != svn_node_dir)
    eb.anchor_abspath = svn_dirent_dirname(local_abspath, scratch_pool);

  if (root_relpath)
    *root_relpath = apr_pstrdup(result_pool,
                                svn_dirent_skip_ancestor(eb.anchor_abspath,
                                                         local_abspath));
  if (root_is_dir)
    *root_is_dir = (kind == svn_node_dir);

  /* Apply changelist filtering to the output */
  if (changelist_filter && changelist_filter->nelts)
    {
      apr_hash_t *changelist_hash;

      SVN_ERR(svn_hash_from_cstring_keys(&changelist_hash, changelist_filter,
                                         result_pool));
      diff_processor = svn_wc__changelist_filter_tree_processor_create(
                         diff_processor, wc_ctx, local_abspath,
                         changelist_hash, result_pool);
    }

  eb.db = wc_ctx->db;
  eb.processor = diff_processor;
  eb.ignore_ancestry = ignore_ancestry;
  eb.pool = scratch_pool;

  if (ignore_ancestry)
    get_all = TRUE; /* We need unmodified descendants of copies */
  else
    get_all = FALSE;

  /* Walk status handles files and directories */
  SVN_ERR(svn_wc__internal_walk_status(wc_ctx->db, local_abspath, depth,
                                       get_all,
                                       TRUE /* no_ignore */,
                                       FALSE /* ignore_text_mods */,
                                       NULL /* ignore_patterns */,
                                       diff_status_callback, &eb,
                                       cancel_func, cancel_baton,
                                       scratch_pool));

  /* Close the remaining open directories */
  while (eb.cur)
    {
      struct node_state_t *ns = eb.cur;

      if (!ns->skip)
        {
          if (ns->propchanges)
            SVN_ERR(diff_processor->dir_changed(ns->relpath,
                                                ns->left_src,
                                                ns->right_src,
                                                ns->left_props,
                                                ns->right_props,
                                                ns->propchanges,
                                                ns->baton,
                                                diff_processor,
                                                ns->pool));
          else
            SVN_ERR(diff_processor->dir_closed(ns->relpath,
                                               ns->left_src,
                                               ns->right_src,
                                               ns->baton,
                                               diff_processor,
                                               ns->pool));
        }
      eb.cur = ns->parent;
      svn_pool_clear(ns->pool);
    }

  return SVN_NO_ERROR;
}
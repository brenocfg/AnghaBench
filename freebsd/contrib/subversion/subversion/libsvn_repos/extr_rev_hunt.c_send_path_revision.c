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
typedef  scalar_t__ svn_txdelta_window_handler_t ;
typedef  int /*<<< orphan*/  svn_txdelta_stream_t ;
struct TYPE_3__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ svn_repos_t ;
typedef  int /*<<< orphan*/  svn_prop_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  (* svn_file_rev_handler_t ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct send_baton {int /*<<< orphan*/ * last_pool; int /*<<< orphan*/ * iterpool; int /*<<< orphan*/ * last_props; int /*<<< orphan*/  last_path; int /*<<< orphan*/ * last_root; scalar_t__ include_merged_revisions; } ;
struct path_revision {int /*<<< orphan*/  path; int /*<<< orphan*/  merged; int /*<<< orphan*/  revnum; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/ * apr_array_make (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_delta_noop_window_handler ; 
 int /*<<< orphan*/  svn_fs_contents_different (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_get_file_delta_stream (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_node_proplist (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_props_changed (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_revision_proplist2 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_revision_root (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_prop_diffs (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_prop_hash_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_txdelta_send_txstream (int /*<<< orphan*/ *,scalar_t__,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
send_path_revision(struct path_revision *path_rev,
                   svn_repos_t *repos,
                   struct send_baton *sb,
                   svn_file_rev_handler_t handler,
                   void *handler_baton)
{
  apr_hash_t *rev_props;
  apr_hash_t *props;
  apr_array_header_t *prop_diffs;
  svn_fs_root_t *root;
  svn_txdelta_stream_t *delta_stream;
  svn_txdelta_window_handler_t delta_handler = NULL;
  void *delta_baton = NULL;
  apr_pool_t *tmp_pool;  /* For swapping */
  svn_boolean_t contents_changed;
  svn_boolean_t props_changed;

  svn_pool_clear(sb->iterpool);

  /* Get the revision properties. */
  SVN_ERR(svn_fs_revision_proplist2(&rev_props, repos->fs,
                                    path_rev->revnum, FALSE,
                                    sb->iterpool, sb->iterpool));

  /* Open the revision root. */
  SVN_ERR(svn_fs_revision_root(&root, repos->fs, path_rev->revnum,
                               sb->iterpool));

  /* Check if the props *may* have changed. */
  if (sb->last_root)
    {
      /* We don't use svn_fs_props_different() because it's more
       * expensive. */
      SVN_ERR(svn_fs_props_changed(&props_changed,
                                   sb->last_root, sb->last_path,
                                   root, path_rev->path, sb->iterpool));
    }
  else
    {
      props_changed = TRUE;
    }

  /* Calculate actual difference between last and current properties. */
  if (props_changed)
    {
      /* Get the file's properties for this revision and compute the diffs. */
      SVN_ERR(svn_fs_node_proplist(&props, root, path_rev->path,
                                   sb->iterpool));
      SVN_ERR(svn_prop_diffs(&prop_diffs, props, sb->last_props,
                             sb->iterpool));
    }
  else
    {
      /* Properties didn't change: copy  LAST_PROPS to current POOL. */
      props = svn_prop_hash_dup(sb->last_props, sb->iterpool);
      prop_diffs = apr_array_make(sb->iterpool, 0, sizeof(svn_prop_t));
    }

  /* Check if the contents *may* have changed. */
  if (! sb->last_root)
    {
      /* Special case: In the first revision, we always provide a delta. */
      contents_changed = TRUE;
    }
  else if (sb->include_merged_revisions
           && strcmp(sb->last_path, path_rev->path))
    {
      /* ### This is a HACK!!!
       * Blame -g, in older clients anyways, relies on getting a notification
       * whenever the path changes - even if there was no content change.
       *
       * TODO: A future release should take an extra parameter and depending
       * on that either always send a text delta or only send it if there
       * is a difference. */
      contents_changed = TRUE;
    }
  else
    {
      /* Did the file contents actually change?
       * It could e.g. be a property-only change. */
      SVN_ERR(svn_fs_contents_different(&contents_changed, sb->last_root,
                                        sb->last_path, root, path_rev->path,
                                        sb->iterpool));
    }

  /* We have all we need, give to the handler. */
  SVN_ERR(handler(handler_baton, path_rev->path, path_rev->revnum,
                  rev_props, path_rev->merged,
                  contents_changed ? &delta_handler : NULL,
                  contents_changed ? &delta_baton : NULL,
                  prop_diffs, sb->iterpool));

  /* Compute and send delta if client asked for it.
     Note that this was initialized to NULL, so if !contents_changed,
     no deltas will be computed. */
  if (delta_handler && delta_handler != svn_delta_noop_window_handler)
    {
      /* Get the content delta. */
      SVN_ERR(svn_fs_get_file_delta_stream(&delta_stream,
                                           sb->last_root, sb->last_path,
                                           root, path_rev->path,
                                           sb->iterpool));
      /* And send. */
      SVN_ERR(svn_txdelta_send_txstream(delta_stream,
                                        delta_handler, delta_baton,
                                        sb->iterpool));
    }

  /* Remember root, path and props for next iteration. */
  sb->last_root = root;
  sb->last_path = path_rev->path;
  sb->last_props = props;

  /* Swap the pools. */
  tmp_pool = sb->iterpool;
  sb->iterpool = sb->last_pool;
  sb->last_pool = tmp_pool;

  return SVN_NO_ERROR;
}
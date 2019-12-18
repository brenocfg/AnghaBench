#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
struct TYPE_11__ {TYPE_4__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_history_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
struct TYPE_12__ {int /*<<< orphan*/ * node; } ;
typedef  TYPE_2__ parent_path_t ;
struct TYPE_13__ {char const* created_path; int /*<<< orphan*/  const* predecessor_id; } ;
typedef  TYPE_3__ node_revision_t ;
struct TYPE_14__ {char* path; scalar_t__ revision; int is_interesting; scalar_t__ next_copy; char* path_hint; scalar_t__ rev_hint; scalar_t__ current_id; int /*<<< orphan*/ * fs; } ;
typedef  TYPE_4__ fs_history_data_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_INVALID_REVNUM ; 
 scalar_t__ SVN_IS_VALID_REVNUM (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int TRUE ; 
 TYPE_1__* assemble_history (int /*<<< orphan*/ *,char const*,scalar_t__,int,char const*,scalar_t__,scalar_t__,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  find_youngest_copyroot (scalar_t__*,char const**,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_dag (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_path (TYPE_2__**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__dag_get_copyfrom_path (char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__dag_get_copyfrom_rev (scalar_t__*,int /*<<< orphan*/ *) ; 
 char* svn_fs_fs__dag_get_created_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__dag_get_node (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__dag_get_predecessor_id (int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__dag_get_revision (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__get_node_revision (TYPE_3__**,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_fs__id_rev (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  svn_fs_fs__revision_root (int /*<<< orphan*/ **,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 char* svn_fspath__join (char const*,char const*,int /*<<< orphan*/ *) ; 
 char* svn_fspath__skip_ancestor (char const*,char const*) ; 

__attribute__((used)) static svn_error_t *
history_prev(svn_fs_history_t **prev_history,
             svn_fs_history_t *history,
             svn_boolean_t cross_copies,
             apr_pool_t *result_pool,
             apr_pool_t *scratch_pool)
{
  fs_history_data_t *fhd = history->fsap_data;
  const char *commit_path, *src_path, *path = fhd->path;
  svn_revnum_t commit_rev, src_rev, dst_rev;
  svn_revnum_t revision = fhd->revision;
  svn_fs_t *fs = fhd->fs;
  parent_path_t *parent_path;
  dag_node_t *node;
  svn_fs_root_t *root;
  svn_boolean_t reported = fhd->is_interesting;
  svn_revnum_t copyroot_rev;
  const char *copyroot_path;
  const svn_fs_id_t *pred_id = NULL;

  /* Initialize our return value. */
  *prev_history = NULL;

  /* When following history, there tend to be long sections of linear
     history where there are no copies at PATH or its parents.  Within
     these sections, we only need to follow the node history. */
  if (   SVN_IS_VALID_REVNUM(fhd->next_copy)
      && revision > fhd->next_copy
      && fhd->current_id)
    {
      /* We know the last reported node (CURRENT_ID) and the NEXT_COPY
         revision is somewhat further in the past. */
      node_revision_t *noderev;
      assert(reported);

      /* Get the previous node change.  If there is none, then we already
         reported the initial addition and this history traversal is done. */
      SVN_ERR(svn_fs_fs__get_node_revision(&noderev, fs, fhd->current_id,
                                           scratch_pool, scratch_pool));
      if (! noderev->predecessor_id)
        return SVN_NO_ERROR;

      /* If the previous node change is younger than the next copy, it is
         part of the linear history section. */
      commit_rev = svn_fs_fs__id_rev(noderev->predecessor_id);
      if (commit_rev > fhd->next_copy)
        {
          /* Within the linear history, simply report all node changes and
             continue with the respective predecessor. */
          *prev_history = assemble_history(fs, noderev->created_path,
                                           commit_rev, TRUE, NULL,
                                           SVN_INVALID_REVNUM,
                                           fhd->next_copy,
                                           noderev->predecessor_id,
                                           result_pool);

          return SVN_NO_ERROR;
        }

     /* We hit a copy. Fall back to the standard code path. */
    }

  /* If our last history report left us hints about where to pickup
     the chase, then our last report was on the destination of a
     copy.  If we are crossing copies, start from those locations,
     otherwise, we're all done here.  */
  if (fhd->path_hint && SVN_IS_VALID_REVNUM(fhd->rev_hint))
    {
      reported = FALSE;
      if (! cross_copies)
        return SVN_NO_ERROR;
      path = fhd->path_hint;
      revision = fhd->rev_hint;
    }

  /* Construct a ROOT for the current revision. */
  SVN_ERR(svn_fs_fs__revision_root(&root, fs, revision, scratch_pool));

  /* Open PATH/REVISION, and get its node and a bunch of other
     goodies.  */
  SVN_ERR(open_path(&parent_path, root, path, 0, FALSE, scratch_pool));
  node = parent_path->node;
  commit_path = svn_fs_fs__dag_get_created_path(node);
  SVN_ERR(svn_fs_fs__dag_get_revision(&commit_rev, node, scratch_pool));

  /* The Subversion filesystem is written in such a way that a given
     line of history may have at most one interesting history point
     per filesystem revision.  Either that node was edited (and
     possibly copied), or it was copied but not edited.  And a copy
     source cannot be from the same revision as its destination.  So,
     if our history revision matches its node's commit revision, we
     know that ... */
  if (revision == commit_rev)
    {
      if (! reported)
        {
          /* ... we either have not yet reported on this revision (and
             need now to do so) ... */
          *prev_history = assemble_history(fs, commit_path,
                                           commit_rev, TRUE, NULL,
                                           SVN_INVALID_REVNUM,
                                           SVN_INVALID_REVNUM, NULL,
                                           result_pool);
          return SVN_NO_ERROR;
        }
      else
        {
          /* ... or we *have* reported on this revision, and must now
             progress toward this node's predecessor (unless there is
             no predecessor, in which case we're all done!). */
          SVN_ERR(svn_fs_fs__dag_get_predecessor_id(&pred_id, node));
          if (! pred_id)
            return SVN_NO_ERROR;

          /* Replace NODE and friends with the information from its
             predecessor. */
          SVN_ERR(svn_fs_fs__dag_get_node(&node, fs, pred_id, scratch_pool));
          commit_path = svn_fs_fs__dag_get_created_path(node);
          SVN_ERR(svn_fs_fs__dag_get_revision(&commit_rev, node, scratch_pool));
        }
    }

  /* Find the youngest copyroot in the path of this node, including
     itself. */
  SVN_ERR(find_youngest_copyroot(&copyroot_rev, &copyroot_path, fs,
                                 parent_path, scratch_pool));

  /* Initialize some state variables. */
  src_path = NULL;
  src_rev = SVN_INVALID_REVNUM;
  dst_rev = SVN_INVALID_REVNUM;

  if (copyroot_rev > commit_rev)
    {
      const char *remainder_path;
      const char *copy_dst, *copy_src;
      svn_fs_root_t *copyroot_root;

      SVN_ERR(svn_fs_fs__revision_root(&copyroot_root, fs, copyroot_rev,
                                       scratch_pool));
      SVN_ERR(get_dag(&node, copyroot_root, copyroot_path, scratch_pool));
      copy_dst = svn_fs_fs__dag_get_created_path(node);

      /* If our current path was the very destination of the copy,
         then our new current path will be the copy source.  If our
         current path was instead the *child* of the destination of
         the copy, then figure out its previous location by taking its
         path relative to the copy destination and appending that to
         the copy source.  Finally, if our current path doesn't meet
         one of these other criteria ... ### for now just fallback to
         the old copy hunt algorithm. */
      remainder_path = svn_fspath__skip_ancestor(copy_dst, path);

      if (remainder_path)
        {
          /* If we get here, then our current path is the destination
             of, or the child of the destination of, a copy.  Fill
             in the return values and get outta here.  */
          SVN_ERR(svn_fs_fs__dag_get_copyfrom_rev(&src_rev, node));
          SVN_ERR(svn_fs_fs__dag_get_copyfrom_path(&copy_src, node));

          dst_rev = copyroot_rev;
          src_path = svn_fspath__join(copy_src, remainder_path, scratch_pool);
        }
    }

  /* If we calculated a copy source path and revision, we'll make a
     'copy-style' history object. */
  if (src_path && SVN_IS_VALID_REVNUM(src_rev))
    {
      svn_boolean_t retry = FALSE;

      /* It's possible for us to find a copy location that is the same
         as the history point we've just reported.  If that happens,
         we simply need to take another trip through this history
         search. */
      if ((dst_rev == revision) && reported)
        retry = TRUE;

      *prev_history = assemble_history(fs, path, dst_rev, ! retry,
                                       src_path, src_rev,
                                       SVN_INVALID_REVNUM, NULL,
                                       result_pool);
    }
  else
    {
      /* We know the next copy revision.  If we are not at the copy rev
         itself, we will also know the predecessor node ID and the next
         invocation will use the optimized "linear history" code path. */
      *prev_history = assemble_history(fs, commit_path, commit_rev, TRUE,
                                       NULL, SVN_INVALID_REVNUM,
                                       copyroot_rev, pred_id, result_pool);
    }

  return SVN_NO_ERROR;
}
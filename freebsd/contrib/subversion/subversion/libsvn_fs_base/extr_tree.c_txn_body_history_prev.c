#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ trail_t ;
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
struct TYPE_22__ {TYPE_5__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_history_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
struct revision_root_args {scalar_t__ rev; int /*<<< orphan*/ ** root_p; } ;
struct history_prev_args {int /*<<< orphan*/  cross_copies; int /*<<< orphan*/ * pool; TYPE_2__* history; TYPE_2__** prev_history_p; } ;
struct TYPE_23__ {int /*<<< orphan*/ * node; } ;
typedef  TYPE_3__ parent_path_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
struct TYPE_24__ {scalar_t__ kind; int /*<<< orphan*/  src_path; int /*<<< orphan*/  const* dst_noderev_id; int /*<<< orphan*/  src_txn_id; } ;
typedef  TYPE_4__ copy_t ;
struct TYPE_25__ {char* path; scalar_t__ revision; int is_interesting; char* path_hint; scalar_t__ rev_hint; int /*<<< orphan*/ * fs; } ;
typedef  TYPE_5__ base_history_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_INVALID_REVNUM ; 
 scalar_t__ SVN_IS_VALID_REVNUM (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int TRUE ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 TYPE_2__* assemble_history (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int,char const*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ copy_kind_soft ; 
 int /*<<< orphan*/  examine_copy_inheritance (char const**,TYPE_4__**,int /*<<< orphan*/ *,TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_path (TYPE_3__**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char const*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 char* svn_fs_base__dag_get_created_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_base__dag_get_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__dag_get_node (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__dag_get_predecessor_id (int /*<<< orphan*/  const**,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__dag_get_revision (scalar_t__*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__id_copy_id (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  svn_fs_base__id_txn_id (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  svn_fs_base__rev_get_txn_id (char const**,int /*<<< orphan*/ *,scalar_t__,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__txn_get_revision (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_bdb__get_copy (TYPE_4__**,int /*<<< orphan*/ *,char const*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 char* svn_fspath__join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 char* svn_fspath__skip_ancestor (char const*,char const*) ; 
 int /*<<< orphan*/  txn_body_revision_root (struct revision_root_args*,TYPE_1__*) ; 

__attribute__((used)) static svn_error_t *
txn_body_history_prev(void *baton, trail_t *trail)
{
  struct history_prev_args *args = baton;
  svn_fs_history_t **prev_history = args->prev_history_p;
  svn_fs_history_t *history = args->history;
  base_history_data_t *bhd = history->fsap_data;
  const char *commit_path, *src_path, *path = bhd->path;
  svn_revnum_t commit_rev, src_rev, dst_rev, revision = bhd->revision;
  apr_pool_t *retpool = args->pool;
  svn_fs_t *fs = bhd->fs;
  parent_path_t *parent_path;
  dag_node_t *node;
  svn_fs_root_t *root;
  const svn_fs_id_t *node_id;
  const char *end_copy_id = NULL;
  struct revision_root_args rr_args;
  svn_boolean_t reported = bhd->is_interesting;
  const char *txn_id;
  copy_t *copy = NULL;
  svn_boolean_t retry = FALSE;

  /* Initialize our return value. */
  *prev_history = NULL;

  /* If our last history report left us hints about where to pickup
     the chase, then our last report was on the destination of a
     copy.  If we are crossing copies, start from those locations,
     otherwise, we're all done here.  */
  if (bhd->path_hint && SVN_IS_VALID_REVNUM(bhd->rev_hint))
    {
      reported = FALSE;
      if (! args->cross_copies)
        return SVN_NO_ERROR;
      path = bhd->path_hint;
      revision = bhd->rev_hint;
    }

  /* Construct a ROOT for the current revision. */
  rr_args.root_p = &root;
  rr_args.rev = revision;
  SVN_ERR(txn_body_revision_root(&rr_args, trail));

  /* Open PATH/REVISION, and get its node and a bunch of other
     goodies.  */
  SVN_ERR(svn_fs_base__rev_get_txn_id(&txn_id, fs, revision, trail,
                                      trail->pool));
  SVN_ERR(open_path(&parent_path, root, path, 0, txn_id,
                    trail, trail->pool));
  node = parent_path->node;
  node_id = svn_fs_base__dag_get_id(node);
  commit_path = svn_fs_base__dag_get_created_path(node);
  SVN_ERR(svn_fs_base__dag_get_revision(&commit_rev, node,
                                        trail, trail->pool));

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
          *prev_history = assemble_history(fs,
                                           apr_pstrdup(retpool, commit_path),
                                           commit_rev, TRUE, NULL,
                                           SVN_INVALID_REVNUM, retpool);
          return SVN_NO_ERROR;
        }
      else
        {
          /* ... or we *have* reported on this revision, and must now
             progress toward this node's predecessor (unless there is
             no predecessor, in which case we're all done!). */
          const svn_fs_id_t *pred_id;

          SVN_ERR(svn_fs_base__dag_get_predecessor_id(&pred_id, node,
                                                      trail, trail->pool));
          if (! pred_id)
            return SVN_NO_ERROR;

          /* Replace NODE and friends with the information from its
             predecessor. */
          SVN_ERR(svn_fs_base__dag_get_node(&node, fs, pred_id,
                                            trail, trail->pool));
          node_id = svn_fs_base__dag_get_id(node);
          commit_path = svn_fs_base__dag_get_created_path(node);
          SVN_ERR(svn_fs_base__dag_get_revision(&commit_rev, node,
                                                trail, trail->pool));
        }
    }

  /* Calculate a possibly relevant copy ID. */
  SVN_ERR(examine_copy_inheritance(&end_copy_id, &copy, fs,
                                   parent_path, trail, trail->pool));

  /* Initialize some state variables. */
  src_path = NULL;
  src_rev = SVN_INVALID_REVNUM;
  dst_rev = SVN_INVALID_REVNUM;

  /* If our current copy ID (which is either the real copy ID of our
     node, or the last copy ID which would affect our node if it were
     to be made mutable) diffs at all from that of its predecessor
     (which is either a real predecessor, or is the node itself
     playing the predecessor role to an imaginary mutable successor),
     then we need to report a copy.  */
  if (strcmp(svn_fs_base__id_copy_id(node_id), end_copy_id) != 0)
    {
      const char *remainder;
      dag_node_t *dst_node;
      const char *copy_dst;

      /* Get the COPY record if we haven't already fetched it. */
      if (! copy)
        SVN_ERR(svn_fs_bdb__get_copy(&copy, fs, end_copy_id, trail,
                                     trail->pool));

      /* Figure out the destination path of the copy operation. */
      SVN_ERR(svn_fs_base__dag_get_node(&dst_node, fs,
                                        copy->dst_noderev_id,
                                        trail, trail->pool));
      copy_dst = svn_fs_base__dag_get_created_path(dst_node);

      /* If our current path was the very destination of the copy,
         then our new current path will be the copy source.  If our
         current path was instead the *child* of the destination of
         the copy, then figure out its previous location by taking its
         path relative to the copy destination and appending that to
         the copy source.  Finally, if our current path doesn't meet
         one of these other criteria ... ### for now just fallback to
         the old copy hunt algorithm. */
      remainder = svn_fspath__skip_ancestor(copy_dst, path);

      if (remainder)
        {
          /* If we get here, then our current path is the destination
             of, or the child of the destination of, a copy.  Fill
             in the return values and get outta here.  */
          SVN_ERR(svn_fs_base__txn_get_revision
                  (&src_rev, fs, copy->src_txn_id, trail, trail->pool));
          SVN_ERR(svn_fs_base__txn_get_revision
                  (&dst_rev, fs,
                   svn_fs_base__id_txn_id(copy->dst_noderev_id),
                   trail, trail->pool));
          src_path = svn_fspath__join(copy->src_path, remainder,
                                     trail->pool);
          if (copy->kind == copy_kind_soft)
            retry = TRUE;
        }
    }

  /* If we calculated a copy source path and revision, and the
     copy source revision doesn't pre-date a revision in which we
     *know* our node was modified, we'll make a 'copy-style' history
     object. */
  if (src_path && SVN_IS_VALID_REVNUM(src_rev) && (src_rev >= commit_rev))
    {
      /* It's possible for us to find a copy location that is the same
         as the history point we've just reported.  If that happens,
         we simply need to take another trip through this history
         search. */
      if ((dst_rev == revision) && reported)
        retry = TRUE;

      *prev_history = assemble_history(fs, apr_pstrdup(retpool, path),
                                       dst_rev, ! retry,
                                       src_path, src_rev, retpool);
    }
  else
    {
      *prev_history = assemble_history(fs, apr_pstrdup(retpool, commit_path),
                                       commit_rev, TRUE, NULL,
                                       SVN_INVALID_REVNUM, retpool);
    }

  return SVN_NO_ERROR;
}
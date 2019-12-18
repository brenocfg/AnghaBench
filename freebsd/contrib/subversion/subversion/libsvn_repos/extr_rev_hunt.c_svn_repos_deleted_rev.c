#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  scalar_t__ svn_fs_node_relation_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_NO_SUCH_REVISION ; 
 scalar_t__ SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  svn_fs_check_path (scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_closest_copy (int /*<<< orphan*/ **,char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_node_relation (scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_node_unrelated ; 
 int /*<<< orphan*/  svn_fs_revision_root (int /*<<< orphan*/ **,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_revision_root_revision (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_none ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_repos_deleted_rev(svn_fs_t *fs,
                      const char *path,
                      svn_revnum_t start,
                      svn_revnum_t end,
                      svn_revnum_t *deleted,
                      apr_pool_t *pool)
{
  apr_pool_t *iterpool;
  svn_fs_root_t *start_root, *root;
  svn_revnum_t mid_rev;
  svn_node_kind_t kind;
  svn_fs_node_relation_t node_relation;

  /* Validate the revision range. */
  if (! SVN_IS_VALID_REVNUM(start))
    return svn_error_createf
      (SVN_ERR_FS_NO_SUCH_REVISION, 0,
       _("Invalid start revision %ld"), start);
  if (! SVN_IS_VALID_REVNUM(end))
    return svn_error_createf
      (SVN_ERR_FS_NO_SUCH_REVISION, 0,
       _("Invalid end revision %ld"), end);

  /* Ensure that the input is ordered. */
  if (start > end)
    {
      svn_revnum_t tmprev = start;
      start = end;
      end = tmprev;
    }

  /* Ensure path exists in fs at start revision. */
  SVN_ERR(svn_fs_revision_root(&start_root, fs, start, pool));
  SVN_ERR(svn_fs_check_path(&kind, start_root, path, pool));
  if (kind == svn_node_none)
    {
      /* Path must exist in fs at start rev. */
      *deleted = SVN_INVALID_REVNUM;
      return SVN_NO_ERROR;
    }

  /* Ensure path was deleted at or before end revision. */
  SVN_ERR(svn_fs_revision_root(&root, fs, end, pool));
  SVN_ERR(svn_fs_check_path(&kind, root, path, pool));
  if (kind != svn_node_none)
    {
      /* path exists in the end node and the end node is equivalent
         or otherwise equivalent to the start node.  This can mean
         a few things:

           1) The end node *is* simply the start node, uncopied
              and unmodified in the start to end range.

           2) The start node was modified, but never copied.

           3) The start node was copied, but this copy occurred at
              start or some rev *previous* to start, this is
              effectively the same situation as 1 if the node was
              never modified or 2 if it was.

         In the first three cases the path was not deleted in
         the specified range and we are done, but in the following
         cases the start node must have been deleted at least once:

           4) The start node was deleted and replaced by a copy of
              itself at some rev between start and end.  This copy
              may itself have been replaced with copies of itself.

           5) The start node was deleted and replaced by a node which
              it does not share any history with.
      */
      SVN_ERR(svn_fs_node_relation(&node_relation, start_root, path,
                                   root, path, pool));
      if (node_relation != svn_fs_node_unrelated)
        {
          svn_fs_root_t *copy_root;
          const char *copy_path;
          SVN_ERR(svn_fs_closest_copy(&copy_root, &copy_path, root,
                                      path, pool));
          if (!copy_root ||
              (svn_fs_revision_root_revision(copy_root) <= start))
            {
              /* Case 1,2 or 3, nothing more to do. */
              *deleted = SVN_INVALID_REVNUM;
              return SVN_NO_ERROR;
            }
        }
    }

  /* If we get here we know that path exists in rev start and was deleted
     at least once before rev end.  To find the revision path was first
     deleted we use a binary search.  The rules for the determining if
     the deletion comes before or after a given median revision are
     described by this matrix:

                   |             Most recent copy event that
                   |               caused mid node to exist.
                   |-----------------------------------------------------
     Compare path  |                   |                |               |
     at start and  |   Copied at       |  Copied at     | Never copied  |
     mid nodes.    |   rev > start     |  rev <= start  |               |
                   |                   |                |               |
     -------------------------------------------------------------------|
     Mid node is   |  A) Start node    |                                |
     equivalent to |     replaced with |  E) Mid node == start node,    |
     start node    |     an unmodified |     look HIGHER.               |
                   |     copy of       |                                |
                   |     itself,       |                                |
                   |     look LOWER.   |                                |
     -------------------------------------------------------------------|
     Mid node is   |  B) Start node    |                                |
     otherwise     |     replaced with |  F) Mid node is a modified     |
     related to    |     a modified    |     version of start node,     |
     start node    |     copy of       |     look HIGHER.               |
                   |     itself,       |                                |
                   |     look LOWER.   |                                |
     -------------------------------------------------------------------|
     Mid node is   |                                                    |
     unrelated to  |  C) Start node replaced with unrelated mid node,   |
     start node    |     look LOWER.                                    |
                   |                                                    |
     -------------------------------------------------------------------|
     Path doesn't  |                                                    |
     exist at mid  |  D) Start node deleted before mid node,            |
     node          |     look LOWER                                     |
                   |                                                    |
     --------------------------------------------------------------------
  */

  mid_rev = (start + end) / 2;
  iterpool = svn_pool_create(pool);

  while (1)
    {
      svn_pool_clear(iterpool);

      /* Get revision root and node id for mid_rev at that revision. */
      SVN_ERR(svn_fs_revision_root(&root, fs, mid_rev, iterpool));
      SVN_ERR(svn_fs_check_path(&kind, root, path, iterpool));
      if (kind == svn_node_none)
        {
          /* Case D: Look lower in the range. */
          end = mid_rev;
          mid_rev = (start + mid_rev) / 2;
        }
      else
        {
          svn_fs_root_t *copy_root;
          const char *copy_path;
          /* Determine the relationship between the start node
             and the current node. */
          SVN_ERR(svn_fs_node_relation(&node_relation, start_root, path,
                                       root, path, iterpool));
          if (node_relation != svn_fs_node_unrelated)
            SVN_ERR(svn_fs_closest_copy(&copy_root, &copy_path, root,
                                        path, iterpool));
          if (node_relation == svn_fs_node_unrelated ||
              (copy_root &&
               (svn_fs_revision_root_revision(copy_root) > start)))
            {
              /* Cases A, B, C: Look at lower revs. */
              end = mid_rev;
              mid_rev = (start + mid_rev) / 2;
            }
          else if (end - mid_rev == 1)
            {
              /* Found the node path was deleted. */
              *deleted = end;
              break;
            }
          else
            {
              /* Cases E, F: Look at higher revs. */
              start = mid_rev;
              mid_rev = (start + end) / 2;
            }
        }
    }

  svn_pool_destroy(iterpool);
  return SVN_NO_ERROR;
}
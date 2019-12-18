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
typedef  int /*<<< orphan*/  svn_repos_notify_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
struct revision_baton {int /*<<< orphan*/  txn_root; int /*<<< orphan*/  rev; scalar_t__ rev_offset; struct parse_baton* pb; } ;
struct parse_baton {int /*<<< orphan*/  notify_pool; int /*<<< orphan*/  notify_baton; int /*<<< orphan*/  (* notify_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  fs; int /*<<< orphan*/  rev_map; int /*<<< orphan*/  use_history; } ;
struct node_baton {scalar_t__ kind; int /*<<< orphan*/  path; int /*<<< orphan*/ * copyfrom_path; scalar_t__ copy_source_checksum; scalar_t__ copyfrom_rev; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_NO_SUCH_REVISION ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ get_revision_mapping (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_checksum_match (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_md5 ; 
 int /*<<< orphan*/ * svn_checksum_mismatch_err (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  svn_fs_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_file_checksum (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_make_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_make_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_revision_root (int /*<<< orphan*/ **,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_repos_notify_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_repos_notify_load_copied_node ; 

__attribute__((used)) static svn_error_t *
maybe_add_with_history(struct node_baton *nb,
                       struct revision_baton *rb,
                       apr_pool_t *pool)
{
  struct parse_baton *pb = rb->pb;

  if ((nb->copyfrom_path == NULL) || (! pb->use_history))
    {
      /* Add empty file or dir, without history. */
      if (nb->kind == svn_node_file)
        SVN_ERR(svn_fs_make_file(rb->txn_root, nb->path, pool));

      else if (nb->kind == svn_node_dir)
        SVN_ERR(svn_fs_make_dir(rb->txn_root, nb->path, pool));
    }
  else
    {
      /* Hunt down the source revision in this fs. */
      svn_fs_root_t *copy_root;
      svn_revnum_t copyfrom_rev;

      /* Try to find the copyfrom revision in the revision map;
         failing that, fall back to the revision offset approach. */
      copyfrom_rev = get_revision_mapping(rb->pb->rev_map, nb->copyfrom_rev);
      if (! SVN_IS_VALID_REVNUM(copyfrom_rev))
        copyfrom_rev = nb->copyfrom_rev - rb->rev_offset;

      if (! SVN_IS_VALID_REVNUM(copyfrom_rev))
        return svn_error_createf(SVN_ERR_FS_NO_SUCH_REVISION, NULL,
                                 _("Relative source revision %ld is not"
                                   " available in current repository"),
                                 copyfrom_rev);

      SVN_ERR(svn_fs_revision_root(&copy_root, pb->fs, copyfrom_rev, pool));

      if (nb->copy_source_checksum)
        {
          svn_checksum_t *checksum;
          SVN_ERR(svn_fs_file_checksum(&checksum, svn_checksum_md5, copy_root,
                                       nb->copyfrom_path, TRUE, pool));
          if (!svn_checksum_match(nb->copy_source_checksum, checksum))
            return svn_checksum_mismatch_err(nb->copy_source_checksum,
                      checksum, pool,
                      _("Copy source checksum mismatch on copy from '%s'@%ld\n"
                        "to '%s' in rev based on r%ld"),
                      nb->copyfrom_path, copyfrom_rev, nb->path, rb->rev);
        }

      SVN_ERR(svn_fs_copy(copy_root, nb->copyfrom_path,
                          rb->txn_root, nb->path, pool));

      if (pb->notify_func)
        {
          /* ### TODO: Use proper scratch pool instead of pb->notify_pool */
          svn_repos_notify_t *notify = svn_repos_notify_create(
                                            svn_repos_notify_load_copied_node,
                                            pb->notify_pool);

          pb->notify_func(pb->notify_baton, notify, pb->notify_pool);
          svn_pool_clear(pb->notify_pool);
        }
    }

  return SVN_NO_ERROR;
}
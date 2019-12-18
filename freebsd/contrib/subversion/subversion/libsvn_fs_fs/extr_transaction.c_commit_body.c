#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_41__   TYPE_5__ ;
typedef  struct TYPE_40__   TYPE_4__ ;
typedef  struct TYPE_39__   TYPE_3__ ;
typedef  struct TYPE_38__   TYPE_2__ ;
typedef  struct TYPE_37__   TYPE_1__ ;

/* Type definitions */
struct TYPE_37__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_fs_fs__id_part_t ;
struct TYPE_38__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
struct commit_baton {TYPE_4__* txn; TYPE_5__* fs; scalar_t__* new_rev_p; int /*<<< orphan*/  reps_pool; int /*<<< orphan*/  reps_hash; int /*<<< orphan*/  reps_to_cache; } ;
typedef  int /*<<< orphan*/  pair_cache_key_t ;
struct TYPE_39__ {scalar_t__ max_files_per_dir; scalar_t__ youngest_rev_cache; scalar_t__ verify_before_commit; scalar_t__ flush_to_disk; } ;
typedef  TYPE_3__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_uint64_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_off_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_file_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;
struct TYPE_41__ {int /*<<< orphan*/  path; TYPE_3__* fsap_data; } ;
struct TYPE_40__ {scalar_t__ base_rev; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int /*<<< orphan*/  APR_STATUS_IS_EEXIST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PATH_REVPROPS_DIR ; 
 int /*<<< orphan*/  PATH_REVS_DIR ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_FS_TXN_OUT_OF_DATE ; 
 TYPE_2__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_array_make (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  get_writable_proto_rev (int /*<<< orphan*/ **,void**,TYPE_5__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  promote_cached_directories (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_join (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 TYPE_2__* svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_error_trace (TYPE_2__*) ; 
 int /*<<< orphan*/  svn_fs_fs__add_index_data (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_fs__id_item (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * svn_fs_fs__id_txn_create_root (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__is_packed_revprop (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  svn_fs_fs__move_into_place (char const*,char const*,char const*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__path_l2p_proto_index (TYPE_5__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__path_p2l_proto_index (TYPE_5__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 char* svn_fs_fs__path_rev (TYPE_5__*,scalar_t__,int /*<<< orphan*/ *) ; 
 char* svn_fs_fs__path_rev_absolute (TYPE_5__*,scalar_t__,int /*<<< orphan*/ *) ; 
 char* svn_fs_fs__path_rev_shard (TYPE_5__*,scalar_t__,int /*<<< orphan*/ *) ; 
 char* svn_fs_fs__path_revprops (TYPE_5__*,scalar_t__,int /*<<< orphan*/ *) ; 
 char* svn_fs_fs__path_revprops_shard (TYPE_5__*,scalar_t__,int /*<<< orphan*/ *) ; 
 char* svn_fs_fs__path_txn_proto_rev (TYPE_5__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__purge_txn (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__read_current (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__read_format_file (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__txn_changes_fetch (int /*<<< orphan*/ **,TYPE_5__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_fs__txn_get_id (TYPE_4__*) ; 
 TYPE_1__* svn_fs_fs__unparse_revision_trailer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_fs__use_log_addressing (TYPE_5__*) ; 
 int /*<<< orphan*/  svn_io_copy_perms (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_io_dir_make (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_flush_to_disk (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_get_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_write_full (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_proto_rev (TYPE_5__*,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify_before_commit (TYPE_5__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify_locks (TYPE_5__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_final_changed_path_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_final_current (TYPE_5__*,int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_final_rev (int /*<<< orphan*/  const**,int /*<<< orphan*/ *,scalar_t__,TYPE_5__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_final_revprop (char const*,char const*,TYPE_4__*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
commit_body(void *baton, apr_pool_t *pool)
{
  struct commit_baton *cb = baton;
  fs_fs_data_t *ffd = cb->fs->fsap_data;
  const char *old_rev_filename, *rev_filename, *proto_filename;
  const char *revprop_filename;
  const svn_fs_id_t *root_id, *new_root_id;
  apr_uint64_t start_node_id;
  apr_uint64_t start_copy_id;
  svn_revnum_t old_rev, new_rev;
  apr_file_t *proto_file;
  void *proto_file_lockcookie;
  apr_off_t initial_offset, changed_path_offset;
  const svn_fs_fs__id_part_t *txn_id = svn_fs_fs__txn_get_id(cb->txn);
  apr_hash_t *changed_paths;
  apr_array_header_t *directory_ids = apr_array_make(pool, 4,
                                                     sizeof(pair_cache_key_t));

  /* Re-Read the current repository format.  All our repo upgrade and
     config evaluation strategies are such that existing information in
     FS and FFD remains valid.

     Although we don't recommend upgrading hot repositories, people may
     still do it and we must make sure to either handle them gracefully
     or to error out.

     Committing pre-format 3 txns will fail after upgrade to format 3+
     because the proto-rev cannot be found; no further action needed.
     Upgrades from pre-f7 to f7+ means a potential change in addressing
     mode for the final rev.  We must be sure to detect that cause because
     the failure would only manifest once the new revision got committed.
   */
  SVN_ERR(svn_fs_fs__read_format_file(cb->fs, pool));

  /* Read the current youngest revision and, possibly, the next available
     node id and copy id (for old format filesystems).  Update the cached
     value for the youngest revision, because we have just checked it. */
  SVN_ERR(svn_fs_fs__read_current(&old_rev, &start_node_id, &start_copy_id,
                                  cb->fs, pool));
  ffd->youngest_rev_cache = old_rev;

  /* Check to make sure this transaction is based off the most recent
     revision. */
  if (cb->txn->base_rev != old_rev)
    return svn_error_create(SVN_ERR_FS_TXN_OUT_OF_DATE, NULL,
                            _("Transaction out of date"));

  /* We need the changes list for verification as well as for writing it
     to the final rev file. */
  SVN_ERR(svn_fs_fs__txn_changes_fetch(&changed_paths, cb->fs, txn_id,
                                       pool));

  /* Locks may have been added (or stolen) between the calling of
     previous svn_fs.h functions and svn_fs_commit_txn(), so we need
     to re-examine every changed-path in the txn and re-verify all
     discovered locks. */
  SVN_ERR(verify_locks(cb->fs, txn_id, changed_paths, pool));

  /* We are going to be one better than this puny old revision. */
  new_rev = old_rev + 1;

  /* Get a write handle on the proto revision file. */
  SVN_ERR(get_writable_proto_rev(&proto_file, &proto_file_lockcookie,
                                 cb->fs, txn_id, pool));
  SVN_ERR(svn_io_file_get_offset(&initial_offset, proto_file, pool));

  /* Write out all the node-revisions and directory contents. */
  root_id = svn_fs_fs__id_txn_create_root(txn_id, pool);
  SVN_ERR(write_final_rev(&new_root_id, proto_file, new_rev, cb->fs, root_id,
                          start_node_id, start_copy_id, initial_offset,
                          directory_ids, cb->reps_to_cache, cb->reps_hash,
                          cb->reps_pool, TRUE, pool));

  /* Write the changed-path information. */
  SVN_ERR(write_final_changed_path_info(&changed_path_offset, proto_file,
                                        cb->fs, txn_id, changed_paths,
                                        pool));

  if (svn_fs_fs__use_log_addressing(cb->fs))
    {
      /* Append the index data to the rev file. */
      SVN_ERR(svn_fs_fs__add_index_data(cb->fs, proto_file,
                      svn_fs_fs__path_l2p_proto_index(cb->fs, txn_id, pool),
                      svn_fs_fs__path_p2l_proto_index(cb->fs, txn_id, pool),
                      new_rev, pool));
    }
  else
    {
      /* Write the final line. */

      svn_stringbuf_t *trailer
        = svn_fs_fs__unparse_revision_trailer
                  ((apr_off_t)svn_fs_fs__id_item(new_root_id),
                   changed_path_offset,
                   pool);
      SVN_ERR(svn_io_file_write_full(proto_file, trailer->data, trailer->len,
                                     NULL, pool));
    }

  if (ffd->flush_to_disk)
    SVN_ERR(svn_io_file_flush_to_disk(proto_file, pool));
  SVN_ERR(svn_io_file_close(proto_file, pool));

  /* We don't unlock the prototype revision file immediately to avoid a
     race with another caller writing to the prototype revision file
     before we commit it. */

  /* Create the shard for the rev and revprop file, if we're sharding and
     this is the first revision of a new shard.  We don't care if this
     fails because the shard already existed for some reason. */
  if (ffd->max_files_per_dir && new_rev % ffd->max_files_per_dir == 0)
    {
      /* Create the revs shard. */
        {
          const char *new_dir
            = svn_fs_fs__path_rev_shard(cb->fs, new_rev, pool);
          svn_error_t *err
            = svn_io_dir_make(new_dir, APR_OS_DEFAULT, pool);
          if (err && !APR_STATUS_IS_EEXIST(err->apr_err))
            return svn_error_trace(err);
          svn_error_clear(err);
          SVN_ERR(svn_io_copy_perms(svn_dirent_join(cb->fs->path,
                                                    PATH_REVS_DIR,
                                                    pool),
                                    new_dir, pool));
        }

      /* Create the revprops shard. */
      SVN_ERR_ASSERT(! svn_fs_fs__is_packed_revprop(cb->fs, new_rev));
        {
          const char *new_dir
            = svn_fs_fs__path_revprops_shard(cb->fs, new_rev, pool);
          svn_error_t *err
            = svn_io_dir_make(new_dir, APR_OS_DEFAULT, pool);
          if (err && !APR_STATUS_IS_EEXIST(err->apr_err))
            return svn_error_trace(err);
          svn_error_clear(err);
          SVN_ERR(svn_io_copy_perms(svn_dirent_join(cb->fs->path,
                                                    PATH_REVPROPS_DIR,
                                                    pool),
                                    new_dir, pool));
        }
    }

  /* Move the finished rev file into place.

     ### This "breaks" the transaction by removing the protorev file
     ### but the revision is not yet complete.  If this commit does
     ### not complete for any reason the transaction will be lost. */
  old_rev_filename = svn_fs_fs__path_rev_absolute(cb->fs, old_rev, pool);
  rev_filename = svn_fs_fs__path_rev(cb->fs, new_rev, pool);
  proto_filename = svn_fs_fs__path_txn_proto_rev(cb->fs, txn_id, pool);
  SVN_ERR(svn_fs_fs__move_into_place(proto_filename, rev_filename,
                                     old_rev_filename, ffd->flush_to_disk,
                                     pool));

  /* Now that we've moved the prototype revision file out of the way,
     we can unlock it (since further attempts to write to the file
     will fail as it no longer exists).  We must do this so that we can
     remove the transaction directory later. */
  SVN_ERR(unlock_proto_rev(cb->fs, txn_id, proto_file_lockcookie, pool));

  /* Write final revprops file. */
  SVN_ERR_ASSERT(! svn_fs_fs__is_packed_revprop(cb->fs, new_rev));
  revprop_filename = svn_fs_fs__path_revprops(cb->fs, new_rev, pool);
  SVN_ERR(write_final_revprop(revprop_filename, old_rev_filename,
                              cb->txn, ffd->flush_to_disk, pool));

  /* Run paranoia checks. */
  if (ffd->verify_before_commit)
    {
      SVN_ERR(verify_before_commit(cb->fs, new_rev, pool));
    }

  /* Update the 'current' file. */
  SVN_ERR(write_final_current(cb->fs, txn_id, new_rev, start_node_id,
                              start_copy_id, pool));

  /* At this point the new revision is committed and globally visible
     so let the caller know it succeeded by giving it the new revision
     number, which fulfills svn_fs_commit_txn() contract.  Any errors
     after this point do not change the fact that a new revision was
     created. */
  *cb->new_rev_p = new_rev;

  ffd->youngest_rev_cache = new_rev;

  /* Make the directory contents alreday cached for the new revision
   * visible. */
  SVN_ERR(promote_cached_directories(cb->fs, directory_ids, pool));

  /* Remove this transaction directory. */
  SVN_ERR(svn_fs_fs__purge_txn(cb->fs, cb->txn->id, pool));

  return SVN_NO_ERROR;
}
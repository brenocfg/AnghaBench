#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_x__txn_id_t ;
typedef  int /*<<< orphan*/  svn_fs_x__pair_cache_key_t ;
typedef  int /*<<< orphan*/  svn_fs_x__id_t ;
struct TYPE_23__ {scalar_t__ youngest_rev_cache; int /*<<< orphan*/  flush_to_disk; } ;
typedef  TYPE_1__ svn_fs_x__data_t ;
typedef  int /*<<< orphan*/  svn_fs_x__batch_fsync_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_24__ {TYPE_3__* txn; TYPE_4__* fs; scalar_t__* new_rev_p; int /*<<< orphan*/  reps_pool; int /*<<< orphan*/  reps_hash; int /*<<< orphan*/  reps_to_cache; } ;
typedef  TYPE_2__ commit_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_off_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_file_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;
struct TYPE_26__ {TYPE_1__* fsap_data; } ;
struct TYPE_25__ {scalar_t__ base_rev; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_FS_TXN_OUT_OF_DATE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_array_make (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  auto_create_shard (TYPE_4__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bump_current (TYPE_4__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_writable_final_rev (int /*<<< orphan*/ **,TYPE_4__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  promote_cached_directories (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__add_index_data (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__batch_fsync_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__init_txn_root (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__is_packed_revprop (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  svn_fs_x__path_l2p_proto_index (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__path_p2l_proto_index (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* svn_fs_x__path_rev (TYPE_4__*,scalar_t__,int /*<<< orphan*/ *) ; 
 char* svn_fs_x__path_rev_absolute (TYPE_4__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__purge_txn (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__read_format_file (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__txn_changes_fetch (int /*<<< orphan*/ **,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__txn_get_id (TYPE_3__*) ; 
 int /*<<< orphan*/  svn_fs_x__youngest_rev (scalar_t__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_copy_perms (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_flush (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_get_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify_as_revision_before_current_plus_plus (TYPE_4__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify_locks (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_final_changed_path_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_final_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_final_revprop (char const**,TYPE_3__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
commit_body(void *baton,
            apr_pool_t *scratch_pool)
{
  commit_baton_t *cb = baton;
  svn_fs_x__data_t *ffd = cb->fs->fsap_data;
  const char *old_rev_filename, *rev_filename;
  const char *revprop_filename;
  svn_fs_x__id_t root_id, new_root_id;
  svn_revnum_t old_rev, new_rev;
  apr_file_t *proto_file;
  apr_off_t initial_offset, changed_path_offset;
  svn_fs_x__txn_id_t txn_id = svn_fs_x__txn_get_id(cb->txn);
  apr_hash_t *changed_paths;
  svn_fs_x__batch_fsync_t *batch;
  apr_array_header_t *directory_ids
    = apr_array_make(scratch_pool, 4, sizeof(svn_fs_x__pair_cache_key_t));

  /* We perform a sequence of (potentially) large allocations.
     Keep the peak memory usage low by using a SUBPOOL and cleaning it
     up frequently. */
  apr_pool_t *subpool = svn_pool_create(scratch_pool);

  /* Re-Read the current repository format.  All our repo upgrade and
     config evaluation strategies are such that existing information in
     FS and FFD remains valid.

     Although we don't recommend upgrading hot repositories, people may
     still do it and we must make sure to either handle them gracefully
     or to error out.
   */
  SVN_ERR(svn_fs_x__read_format_file(cb->fs, subpool));

  /* Get the current youngest revision. */
  SVN_ERR(svn_fs_x__youngest_rev(&old_rev, cb->fs, subpool));
  svn_pool_clear(subpool);

  /* Check to make sure this transaction is based off the most recent
     revision. */
  if (cb->txn->base_rev != old_rev)
    return svn_error_create(SVN_ERR_FS_TXN_OUT_OF_DATE, NULL,
                            _("Transaction out of date"));

  /* We need the changes list for verification as well as for writing it
     to the final rev file. */
  SVN_ERR(svn_fs_x__txn_changes_fetch(&changed_paths, cb->fs, txn_id,
                                      scratch_pool));

  /* Locks may have been added (or stolen) between the calling of
     previous svn_fs.h functions and svn_fs_commit_txn(), so we need
     to re-examine every changed-path in the txn and re-verify all
     discovered locks. */
  SVN_ERR(verify_locks(cb->fs, txn_id, changed_paths, subpool));
  svn_pool_clear(subpool);

  /* We are going to be one better than this puny old revision. */
  new_rev = old_rev + 1;

  /* Use this to force all data to be flushed to physical storage
     (to the degree our environment will allow). */
  SVN_ERR(svn_fs_x__batch_fsync_create(&batch, ffd->flush_to_disk,
                                       scratch_pool));

  /* Set up the target directory. */
  SVN_ERR(auto_create_shard(cb->fs, new_rev, batch, subpool));

  /* Get a write handle on the proto revision file.

     ### This "breaks" the transaction by removing the protorev file
     ### but the revision is not yet complete.  If this commit does
     ### not complete for any reason the transaction will be lost. */
  SVN_ERR(get_writable_final_rev(&proto_file, cb->fs, txn_id, new_rev,
                                 batch, subpool));
  SVN_ERR(svn_io_file_get_offset(&initial_offset, proto_file, subpool));
  svn_pool_clear(subpool);

  /* Write out all the node-revisions and directory contents. */
  svn_fs_x__init_txn_root(&root_id, txn_id);
  SVN_ERR(write_final_rev(&new_root_id, proto_file, new_rev, cb->fs, &root_id,
                          initial_offset, directory_ids, cb->reps_to_cache,
                          cb->reps_hash, cb->reps_pool, TRUE, changed_paths,
                          subpool));
  svn_pool_clear(subpool);

  /* Write the changed-path information. */
  SVN_ERR(write_final_changed_path_info(&changed_path_offset, proto_file,
                                        cb->fs, txn_id, changed_paths,
                                        new_rev, subpool));
  svn_pool_clear(subpool);

  /* Append the index data to the rev file. */
  SVN_ERR(svn_fs_x__add_index_data(cb->fs, proto_file,
                      svn_fs_x__path_l2p_proto_index(cb->fs, txn_id, subpool),
                      svn_fs_x__path_p2l_proto_index(cb->fs, txn_id, subpool),
                      new_rev, subpool));
  svn_pool_clear(subpool);

  /* Set the correct permissions. */
  old_rev_filename = svn_fs_x__path_rev_absolute(cb->fs, old_rev, subpool);
  rev_filename = svn_fs_x__path_rev(cb->fs, new_rev, subpool);
  SVN_ERR(svn_io_copy_perms(rev_filename, old_rev_filename, subpool));

  /* Move the revprops file into place. */
  SVN_ERR_ASSERT(! svn_fs_x__is_packed_revprop(cb->fs, new_rev));
  SVN_ERR(write_final_revprop(&revprop_filename, cb->txn, new_rev, batch,
                              subpool, subpool));
  SVN_ERR(svn_io_copy_perms(revprop_filename, old_rev_filename, subpool));
  svn_pool_clear(subpool);

  /* Verify contents (no-op outside DEBUG mode). */
  SVN_ERR(svn_io_file_flush(proto_file, subpool));
  SVN_ERR(verify_as_revision_before_current_plus_plus(cb->fs, new_rev,
                                                      subpool));

  /* Bump 'current'. */
  SVN_ERR(bump_current(cb->fs, new_rev, batch, subpool));

  /* At this point the new revision is committed and globally visible
     so let the caller know it succeeded by giving it the new revision
     number, which fulfills svn_fs_commit_txn() contract.  Any errors
     after this point do not change the fact that a new revision was
     created. */
  *cb->new_rev_p = new_rev;

  ffd->youngest_rev_cache = new_rev;

  /* Make the directory contents already cached for the new revision
   * visible. */
  SVN_ERR(promote_cached_directories(cb->fs, directory_ids, subpool));

  /* Remove this transaction directory. */
  SVN_ERR(svn_fs_x__purge_txn(cb->fs, cb->txn->id, subpool));

  svn_pool_destroy(subpool);
  return SVN_NO_ERROR;
}
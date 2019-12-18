#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ being_written; } ;
typedef  TYPE_1__ svn_fs_x__shared_txn_data_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {void** lockcookie; int /*<<< orphan*/  txn_id; } ;
typedef  TYPE_2__ get_writable_proto_rev_baton_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int APR_CREATE ; 
 int APR_FLOCK_EXCLUSIVE ; 
 int APR_FLOCK_NONBLOCK ; 
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 scalar_t__ APR_STATUS_IS_EAGAIN (scalar_t__) ; 
 int APR_WRITE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_REP_BEING_WRITTEN ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_file_lock (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* get_shared_txn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* svn_fs_x__path_txn_proto_rev_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__txn_name (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_open (int /*<<< orphan*/ **,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_writable_proto_rev_body(svn_fs_t *fs,
                            const void *baton,
                            apr_pool_t *scratch_pool)
{
  const get_writable_proto_rev_baton_t *b = baton;
  void **lockcookie = b->lockcookie;
  svn_fs_x__shared_txn_data_t *txn = get_shared_txn(fs, b->txn_id, TRUE);

  /* First, ensure that no thread in this process (including this one)
     is currently writing to this transaction's proto-rev file. */
  if (txn->being_written)
    return svn_error_createf(SVN_ERR_FS_REP_BEING_WRITTEN, NULL,
                             _("Cannot write to the prototype revision file "
                               "of transaction '%s' because a previous "
                               "representation is currently being written by "
                               "this process"),
                             svn_fs_x__txn_name(b->txn_id, scratch_pool));


  /* We know that no thread in this process is writing to the proto-rev
     file, and by extension, that no thread in this process is holding a
     lock on the prototype revision lock file.  It is therefore safe
     for us to attempt to lock this file, to see if any other process
     is holding a lock. */

  {
    apr_file_t *lockfile;
    apr_status_t apr_err;
    const char *lockfile_path
      = svn_fs_x__path_txn_proto_rev_lock(fs, b->txn_id, scratch_pool);

    /* Open the proto-rev lockfile, creating it if necessary, as it may
       not exist if the transaction dates from before the lockfiles were
       introduced.

       ### We'd also like to use something like svn_io_file_lock2(), but
           that forces us to create a subpool just to be able to unlock
           the file, which seems a waste. */
    SVN_ERR(svn_io_file_open(&lockfile, lockfile_path,
                             APR_WRITE | APR_CREATE, APR_OS_DEFAULT,
                             scratch_pool));

    apr_err = apr_file_lock(lockfile,
                            APR_FLOCK_EXCLUSIVE | APR_FLOCK_NONBLOCK);
    if (apr_err)
      {
        svn_error_clear(svn_io_file_close(lockfile, scratch_pool));

        if (APR_STATUS_IS_EAGAIN(apr_err))
          return svn_error_createf(SVN_ERR_FS_REP_BEING_WRITTEN, NULL,
                                   _("Cannot write to the prototype revision "
                                     "file of transaction '%s' because a "
                                     "previous representation is currently "
                                     "being written by another process"),
                                   svn_fs_x__txn_name(b->txn_id,
                                                      scratch_pool));

        return svn_error_wrap_apr(apr_err,
                                  _("Can't get exclusive lock on file '%s'"),
                                  svn_dirent_local_style(lockfile_path,
                                                         scratch_pool));
      }

    *lockcookie = lockfile;
  }

  /* We've successfully locked the transaction; mark it as such. */
  txn->being_written = TRUE;

  return SVN_NO_ERROR;
}
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
typedef  int /*<<< orphan*/  svn_fs_x__txn_id_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {void** lockcookie; int /*<<< orphan*/  txn_id; } ;
typedef  TYPE_1__ get_writable_proto_rev_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_off_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int APR_BUFFERED ; 
 int /*<<< orphan*/  APR_END ; 
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int APR_READ ; 
 int APR_WRITE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * auto_truncate_proto_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_writable_proto_rev_body ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__path_txn_proto_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_io_file_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_io_file_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_proto_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  with_txnlist_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_writable_proto_rev(apr_file_t **file,
                       void **lockcookie,
                       svn_fs_t *fs,
                       svn_fs_x__txn_id_t txn_id,
                       apr_pool_t *pool)
{
  get_writable_proto_rev_baton_t b;
  svn_error_t *err;
  apr_off_t end_offset = 0;

  b.lockcookie = lockcookie;
  b.txn_id = txn_id;

  SVN_ERR(with_txnlist_lock(fs, get_writable_proto_rev_body, &b, pool));

  /* Now open the prototype revision file and seek to the end. */
  err = svn_io_file_open(file,
                         svn_fs_x__path_txn_proto_rev(fs, txn_id, pool),
                         APR_READ | APR_WRITE | APR_BUFFERED, APR_OS_DEFAULT,
                         pool);

  /* You might expect that we could dispense with the following seek
     and achieve the same thing by opening the file using APR_APPEND.
     Unfortunately, APR's buffered file implementation unconditionally
     places its initial file pointer at the start of the file (even for
     files opened with APR_APPEND), so we need this seek to reconcile
     the APR file pointer to the OS file pointer (since we need to be
     able to read the current file position later). */
  if (!err)
    err = svn_io_file_seek(*file, APR_END, &end_offset, pool);

  /* We don't want unused sections (such as leftovers from failed delta
     stream) in our file.  If we use log addressing, we would need an
     index entry for the unused section and that section would need to
     be all NUL by convention.  So, detect and fix those cases by truncating
     the protorev file. */
  if (!err)
    err = auto_truncate_proto_rev(fs, *file, end_offset, txn_id, pool);

  if (err)
    {
      err = svn_error_compose_create(
              err,
              unlock_proto_rev(fs, txn_id, *lockcookie, pool));

      *lockcookie = NULL;
    }

  return svn_error_trace(err);
}
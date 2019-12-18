#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_x__txn_id_t ;
struct TYPE_11__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_3__ svn_error_t ;
struct TYPE_12__ {int /*<<< orphan*/  local_pool; int /*<<< orphan*/  lockcookie; int /*<<< orphan*/  fs; int /*<<< orphan*/  file; int /*<<< orphan*/  rep_offset; TYPE_2__* noderev; } ;
typedef  TYPE_4__ rep_write_baton_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
struct TYPE_9__ {int /*<<< orphan*/  change_set; } ;
struct TYPE_10__ {TYPE_1__ noderev_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_3__*) ; 
 TYPE_3__* svn_error_compose_create (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__get_txn_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* svn_io_file_trunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_proto_rev (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static apr_status_t
rep_write_cleanup(void *data)
{
  svn_error_t *err;
  rep_write_baton_t *b = data;
  svn_fs_x__txn_id_t txn_id
    = svn_fs_x__get_txn_id(b->noderev->noderev_id.change_set);

  /* Truncate and close the protorevfile. */
  err = svn_io_file_trunc(b->file, b->rep_offset, b->local_pool);
  err = svn_error_compose_create(err, svn_io_file_close(b->file,
                                                        b->local_pool));

  /* Remove our lock regardless of any preceding errors so that the
     being_written flag is always removed and stays consistent with the
     file lock which will be removed no matter what since the pool is
     going away. */
  err = svn_error_compose_create(err,
                                 unlock_proto_rev(b->fs, txn_id,
                                                  b->lockcookie,
                                                  b->local_pool));
  if (err)
    {
      apr_status_t rc = err->apr_err;
      svn_error_clear(err);
      return rc;
    }

  return APR_SUCCESS;
}
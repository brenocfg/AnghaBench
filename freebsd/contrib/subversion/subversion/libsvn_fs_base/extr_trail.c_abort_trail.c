#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  pool; TYPE_4__* db_txn; TYPE_2__* fs; } ;
typedef  TYPE_1__ trail_t ;
struct TYPE_8__ {TYPE_3__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_9__ {int /*<<< orphan*/  in_txn_trail; } ;
typedef  TYPE_3__ base_fs_data_t ;
struct TYPE_10__ {int /*<<< orphan*/  (* abort ) (TYPE_4__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BDB_WRAP (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
abort_trail(trail_t *trail)
{
  svn_fs_t *fs = trail->fs;
  base_fs_data_t *bfd = fs->fsap_data;

  if (trail->db_txn)
    {
      /* [**]
         We have to reset the in_txn_trail flag *before* calling
         DB_TXN->abort().  If we did it the other way around, the next
         call to begin_trail() (e.g., as part of a txn retry) would
         cause an abort, even though there's strictly speaking no
         programming error involved (see comment [*] above).

         In any case, if aborting the txn fails, restarting it will
         most likely fail for the same reason, and so it's better to
         see the returned error than to abort.  An obvious example is
         when DB_TXN->abort() returns DB_RUNRECOVERY. */
      bfd->in_txn_trail = FALSE;
      SVN_ERR(BDB_WRAP(fs, N_("aborting Berkeley DB transaction"),
                       trail->db_txn->abort(trail->db_txn)));
    }
  svn_pool_destroy(trail->pool);

  return SVN_NO_ERROR;
}
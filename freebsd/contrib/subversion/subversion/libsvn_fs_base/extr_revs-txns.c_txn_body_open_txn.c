#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ kind; int /*<<< orphan*/  base_id; } ;
typedef  TYPE_1__ transaction_t ;
struct TYPE_8__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  fs; } ;
typedef  TYPE_2__ trail_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct open_txn_args {int /*<<< orphan*/  name; int /*<<< orphan*/ * txn_p; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_txn (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_txn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* svn_fs_base__id_txn_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__txn_get_revision (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ transaction_kind_committed ; 

__attribute__((used)) static svn_error_t *
txn_body_open_txn(void *baton, trail_t *trail)
{
  struct open_txn_args *args = baton;
  transaction_t *fstxn;
  svn_revnum_t base_rev = SVN_INVALID_REVNUM;
  const char *txn_id;

  SVN_ERR(get_txn(&fstxn, trail->fs, args->name, FALSE, trail, trail->pool));
  if (fstxn->kind != transaction_kind_committed)
    {
      txn_id = svn_fs_base__id_txn_id(fstxn->base_id);
      SVN_ERR(svn_fs_base__txn_get_revision(&base_rev, trail->fs, txn_id,
                                            trail, trail->pool));
    }

  *args->txn_p = make_txn(trail->fs, args->name, base_rev, trail->pool);
  return SVN_NO_ERROR;
}
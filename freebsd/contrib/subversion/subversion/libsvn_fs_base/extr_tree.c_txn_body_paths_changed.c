#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ trail_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct paths_changed_args {int /*<<< orphan*/  changes; TYPE_1__* root; } ;
struct TYPE_6__ {char* txn; int /*<<< orphan*/  rev; int /*<<< orphan*/  is_txn_root; int /*<<< orphan*/ * fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__rev_get_txn_id (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_bdb__changes_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
txn_body_paths_changed(void *baton,
                       trail_t *trail)
{
  /* WARNING: This is called *without* the protection of a Berkeley DB
     transaction.  If you modify this function, keep that in mind. */

  struct paths_changed_args *args = baton;
  const char *txn_id;
  svn_fs_t *fs = args->root->fs;

  /* Get the transaction ID from ROOT. */
  if (! args->root->is_txn_root)
    SVN_ERR(svn_fs_base__rev_get_txn_id(&txn_id, fs, args->root->rev,
                                        trail, trail->pool));
  else
    txn_id = args->root->txn;

  return svn_fs_bdb__changes_fetch(&(args->changes), fs, txn_id,
                                   trail, trail->pool);
}
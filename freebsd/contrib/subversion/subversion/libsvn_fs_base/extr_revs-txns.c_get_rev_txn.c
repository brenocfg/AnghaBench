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
struct TYPE_6__ {int /*<<< orphan*/  revision; } ;
typedef  TYPE_1__ transaction_t ;
typedef  int /*<<< orphan*/  trail_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {char* txn_id; } ;
typedef  TYPE_2__ revision_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_txn (TYPE_1__**,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_base__err_corrupt_fs_revision (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_base__err_corrupt_txn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_fs_bdb__get_rev (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_rev_txn(transaction_t **txn_p,
            const char **txn_id,
            svn_fs_t *fs,
            svn_revnum_t rev,
            trail_t *trail,
            apr_pool_t *pool)
{
  revision_t *revision;
  transaction_t *txn;

  SVN_ERR(svn_fs_bdb__get_rev(&revision, fs, rev, trail, pool));
  if (revision->txn_id == NULL)
    return svn_fs_base__err_corrupt_fs_revision(fs, rev);

  SVN_ERR(get_txn(&txn, fs, revision->txn_id, FALSE, trail, pool));
  if (txn->revision != rev)
    return svn_fs_base__err_corrupt_txn(fs, revision->txn_id);

  if (txn_p)
    *txn_p = txn;
  if (txn_id)
    *txn_id = revision->txn_id;
  return SVN_NO_ERROR;
}
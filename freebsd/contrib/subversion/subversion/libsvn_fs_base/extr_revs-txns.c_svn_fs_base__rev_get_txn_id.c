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
typedef  int /*<<< orphan*/  trail_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {char* txn_id; } ;
typedef  TYPE_1__ revision_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * svn_fs_base__err_corrupt_fs_revision (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_bdb__get_rev (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_base__rev_get_txn_id(const char **txn_id_p,
                            svn_fs_t *fs,
                            svn_revnum_t rev,
                            trail_t *trail,
                            apr_pool_t *pool)
{
  revision_t *revision;

  SVN_ERR(svn_fs_bdb__get_rev(&revision, fs, rev, trail, pool));
  if (revision->txn_id == NULL)
    return svn_fs_base__err_corrupt_fs_revision(fs, rev);

  *txn_id_p = revision->txn_id;
  return SVN_NO_ERROR;
}
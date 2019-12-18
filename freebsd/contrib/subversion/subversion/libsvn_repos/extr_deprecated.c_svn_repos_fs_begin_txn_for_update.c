#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char const* data; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_6__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_2__ svn_repos_t ;
typedef  int /*<<< orphan*/  svn_fs_txn_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_REVISION_AUTHOR ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  svn_fs_begin_txn2 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_change_txn_prop (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_repos_fs_begin_txn_for_update(svn_fs_txn_t **txn_p,
                                  svn_repos_t *repos,
                                  svn_revnum_t rev,
                                  const char *author,
                                  apr_pool_t *pool)
{
  /* ### someday, we might run a read-hook here. */

  /* Begin the transaction. */
  SVN_ERR(svn_fs_begin_txn2(txn_p, repos->fs, rev, 0, pool));

  /* We pass the author to the filesystem by adding it as a property
     on the txn. */

  /* User (author). */
  if (author)
    {
      svn_string_t val;
      val.data = author;
      val.len = strlen(author);
      SVN_ERR(svn_fs_change_txn_prop(*txn_p, SVN_PROP_REVISION_AUTHOR,
                                     &val, pool));
    }

  return SVN_NO_ERROR;
}
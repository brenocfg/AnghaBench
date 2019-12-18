#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  is_txn_root; } ;
typedef  TYPE_1__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_FS__NOT_TXN (TYPE_1__*) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  copy_helper (TYPE_1__*,char const*,TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* svn_fs__canonicalize_abspath (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
x_revision_link(svn_fs_root_t *from_root,
                svn_fs_root_t *to_root,
                const char *path,
                apr_pool_t *scratch_pool)
{
  apr_pool_t *subpool;

  if (! to_root->is_txn_root)
    return SVN_FS__NOT_TXN(to_root);

  subpool = svn_pool_create(scratch_pool);

  path = svn_fs__canonicalize_abspath(path, subpool);
  SVN_ERR(copy_helper(from_root, path, to_root, path, FALSE, subpool));

  svn_pool_destroy(subpool);

  return SVN_NO_ERROR;
}
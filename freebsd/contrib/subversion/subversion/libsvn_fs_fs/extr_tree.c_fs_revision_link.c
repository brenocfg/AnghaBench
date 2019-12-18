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
 int /*<<< orphan*/ * SVN_FS__NOT_TXN (TYPE_1__*) ; 
 int /*<<< orphan*/  copy_helper (TYPE_1__*,char const*,TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 char* svn_fs__canonicalize_abspath (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
fs_revision_link(svn_fs_root_t *from_root,
                 svn_fs_root_t *to_root,
                 const char *path,
                 apr_pool_t *pool)
{
  if (! to_root->is_txn_root)
    return SVN_FS__NOT_TXN(to_root);

  path = svn_fs__canonicalize_abspath(path, pool);
  return svn_error_trace(copy_helper(from_root, path, to_root, path,
                                     FALSE, pool));
}
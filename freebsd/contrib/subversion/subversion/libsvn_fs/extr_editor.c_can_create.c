#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_OUT_OF_DATE ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_fs_check_path (scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_node_created_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 char* svn_fspath__dirname (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_none ; 

__attribute__((used)) static svn_error_t *
can_create(svn_fs_root_t *txn_root,
           const char *fspath,
           apr_pool_t *scratch_pool)
{
  svn_node_kind_t kind;
  const char *cur_fspath;

  SVN_ERR(svn_fs_check_path(&kind, txn_root, fspath, scratch_pool));
  if (kind == svn_node_none)
    return SVN_NO_ERROR;

  /* ### I'm not sure if this works perfectly. We might have an ancestor
     ### that was modified as a result of a change on a cousin. We might
     ### misinterpret that as a *-here node which brought along this
     ### child. Need to write a test to verify. We may also be able to
     ### test the ancestor to determine if it has been *-here in this
     ### txn, or just a simple modification.  */

  /* Are any of the parents copied/moved-here?  */
  for (cur_fspath = fspath;
       strlen(cur_fspath) > 1;  /* not the root  */
       cur_fspath = svn_fspath__dirname(cur_fspath, scratch_pool))
    {
      svn_revnum_t created_rev;

      SVN_ERR(svn_fs_node_created_rev(&created_rev, txn_root, cur_fspath,
                                      scratch_pool));
      if (!SVN_IS_VALID_REVNUM(created_rev))
        {
          /* The node has no created revision, meaning it is uncommitted.
             Thus, it was created in this transaction, or it has already
             been modified in some way (implying it has already passed a
             modification check.  */
          /* ### verify the node has been *-here ??  */
          return SVN_NO_ERROR;
        }
    }

  return svn_error_createf(SVN_ERR_FS_OUT_OF_DATE, NULL,
                           _("'%s' already exists, so may be out"
                             " of date; try updating"),
                           fspath);
}
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
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct edit_baton {int /*<<< orphan*/  txn; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_FS_NO_SUCH_REVISION ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * out_of_date (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ svn_fs_txn_base_revision (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
check_out_of_date(struct edit_baton *eb,
                  const char *path,
                  svn_node_kind_t kind,
                  svn_revnum_t base_rev,
                  svn_revnum_t created_rev)
{
  if (base_rev < created_rev)
    {
      return out_of_date(path, kind);
    }
  else if (base_rev > created_rev)
    {
      if (base_rev > svn_fs_txn_base_revision(eb->txn))
        return svn_error_createf(SVN_ERR_FS_NO_SUCH_REVISION, NULL, 
                                 _("No such revision %ld"),
                                 base_rev);
    }

  return SVN_NO_ERROR;
}
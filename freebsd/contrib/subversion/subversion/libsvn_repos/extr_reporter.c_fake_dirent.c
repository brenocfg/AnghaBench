#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
struct TYPE_4__ {scalar_t__ kind; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ svn_fs_dirent_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_fs_check_path (scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_node_id (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fspath__basename (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_none ; 
 int /*<<< orphan*/  svn_relpath_basename (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
fake_dirent(const svn_fs_dirent_t **entry, svn_fs_root_t *root,
            const char *path, apr_pool_t *pool)
{
  svn_node_kind_t kind;
  svn_fs_dirent_t *ent;

  SVN_ERR(svn_fs_check_path(&kind, root, path, pool));
  if (kind == svn_node_none)
    *entry = NULL;
  else
    {
      ent = apr_palloc(pool, sizeof(**entry));
      /* ### All callers should be updated to pass just one of these
             formats */
      ent->name = (*path == '/') ? svn_fspath__basename(path, pool)
                                 : svn_relpath_basename(path, pool);
      SVN_ERR(svn_fs_node_id(&ent->id, root, path, pool));
      ent->kind = kind;
      *entry = ent;
    }
  return SVN_NO_ERROR;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int kind; } ;
typedef  TYPE_2__ svn_fs_dirent_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct dir_baton {TYPE_1__* edit_baton; int /*<<< orphan*/  path; } ;
typedef  int /*<<< orphan*/  apr_ssize_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_3__ {int /*<<< orphan*/  fs_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_NODE_UNEXPECTED_KIND ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  svn_fs_is_dir (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_is_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
#define  svn_node_dir 129 
#define  svn_node_file 128 
 char* svn_relpath_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
verify_directory_entry(void *baton, const void *key, apr_ssize_t klen,
                       void *val, apr_pool_t *pool)
{
  struct dir_baton *db = baton;
  svn_fs_dirent_t *dirent = (svn_fs_dirent_t *)val;
  char *path;
  svn_boolean_t right_kind;

  path = svn_relpath_join(db->path, (const char *)key, pool);

  /* since we can't access the directory entries directly by their ID,
     we need to navigate from the FS_ROOT to them (relatively expensive
     because we may start at a never rev than the last change to node).
     We check that the node kind stored in the noderev matches the dir
     entry.  This also ensures that all entries point to valid noderevs.
   */
  switch (dirent->kind) {
  case svn_node_dir:
    SVN_ERR(svn_fs_is_dir(&right_kind, db->edit_baton->fs_root, path, pool));
    if (!right_kind)
      return svn_error_createf(SVN_ERR_NODE_UNEXPECTED_KIND, NULL,
                               _("Node '%s' is not a directory."),
                               path);

    break;
  case svn_node_file:
    SVN_ERR(svn_fs_is_file(&right_kind, db->edit_baton->fs_root, path, pool));
    if (!right_kind)
      return svn_error_createf(SVN_ERR_NODE_UNEXPECTED_KIND, NULL,
                               _("Node '%s' is not a file."),
                               path);
    break;
  default:
    return svn_error_createf(SVN_ERR_NODE_UNEXPECTED_KIND, NULL,
                             _("Unexpected node kind %d for '%s'"),
                             dirent->kind, path);
  }

  return SVN_NO_ERROR;
}
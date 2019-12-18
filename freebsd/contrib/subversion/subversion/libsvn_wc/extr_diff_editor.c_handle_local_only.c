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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_depth_t ;
typedef  int svn_boolean_t ;
struct svn_wc__db_info_t {int status; scalar_t__ kind; scalar_t__ moved_here; } ;
struct edit_baton_t {int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; int /*<<< orphan*/  diff_pristine; int /*<<< orphan*/  processor; int /*<<< orphan*/  db; int /*<<< orphan*/  anchor_abspath; scalar_t__ ignore_ancestry; } ;
struct dir_baton_t {scalar_t__ depth; int /*<<< orphan*/  pdb; int /*<<< orphan*/  relpath; int /*<<< orphan*/  local_abspath; scalar_t__ deletes; scalar_t__ local_info; scalar_t__ skip_children; int /*<<< orphan*/  added; struct edit_baton_t* eb; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ NOT_PRESENT (int) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ensure_local_info (struct dir_baton_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strchr (char const*,char) ; 
 scalar_t__ svn_depth_empty ; 
 scalar_t__ svn_depth_infinity ; 
 scalar_t__ svn_depth_unknown ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_skip_ancestor (int /*<<< orphan*/ ,char const*) ; 
 struct svn_wc__db_info_t* svn_hash_gets (scalar_t__,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (scalar_t__,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 int /*<<< orphan*/  svn_relpath_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_scan_moved (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
#define  svn_wc__db_status_added 131 
#define  svn_wc__db_status_deleted 130 
#define  svn_wc__db_status_incomplete 129 
#define  svn_wc__db_status_normal 128 
 int /*<<< orphan*/  svn_wc__diff_local_only_dir (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,scalar_t__,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__diff_local_only_file (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
handle_local_only(struct dir_baton_t *pb,
                  const char *name,
                  apr_pool_t *scratch_pool)
{
  struct edit_baton_t *eb = pb->eb;
  const struct svn_wc__db_info_t *info;
  const char *child_abspath;
  const char *moved_from_relpath;
  svn_boolean_t repos_delete = (pb->deletes
                                && svn_hash_gets(pb->deletes, name));

  assert(!strchr(name, '/'));
  assert(!pb->added || eb->ignore_ancestry);

  if (pb->skip_children)
    return SVN_NO_ERROR;

  SVN_ERR(ensure_local_info(pb, scratch_pool));

  info = svn_hash_gets(pb->local_info, name);

  if (info == NULL || NOT_PRESENT(info->status))
    return SVN_NO_ERROR;

  switch (info->status)
    {
      case svn_wc__db_status_normal:
      case svn_wc__db_status_incomplete:
        if (!repos_delete)
          return SVN_NO_ERROR; /* Local and remote */
        svn_hash_sets(pb->deletes, name, NULL);
        break;

      case svn_wc__db_status_deleted:
        if (!(eb->diff_pristine && repos_delete))
          return SVN_NO_ERROR;
        break;

      case svn_wc__db_status_added:
      default:
        break;
    }

  child_abspath = svn_dirent_join(pb->local_abspath, name, scratch_pool);

  if (info->moved_here)
    {
      const char *moved_from_abspath;

      SVN_ERR(svn_wc__db_scan_moved(&moved_from_abspath,
                                    NULL, NULL, NULL,
                                    eb->db, child_abspath,
                                    scratch_pool, scratch_pool));
      SVN_ERR_ASSERT(moved_from_abspath != NULL);

      moved_from_relpath = svn_dirent_skip_ancestor(
                                    eb->anchor_abspath,
                                    moved_from_abspath);
    }
  else
    moved_from_relpath = NULL;

  if (info->kind == svn_node_dir)
    {
      svn_depth_t depth ;

      if (pb->depth == svn_depth_infinity || pb->depth == svn_depth_unknown)
        depth = pb->depth;
      else
        depth = svn_depth_empty;

      SVN_ERR(svn_wc__diff_local_only_dir(
                      eb->db,
                      child_abspath,
                      svn_relpath_join(pb->relpath, name, scratch_pool),
                      repos_delete ? svn_depth_infinity : depth,
                      moved_from_relpath,
                      eb->processor, pb->pdb,
                      eb->diff_pristine,
                      eb->cancel_func, eb->cancel_baton,
                      scratch_pool));
    }
  else
    SVN_ERR(svn_wc__diff_local_only_file(
                      eb->db,
                      child_abspath,
                      svn_relpath_join(pb->relpath, name, scratch_pool),
                      moved_from_relpath,
                      eb->processor, pb->pdb,
                      eb->diff_pristine,
                      eb->cancel_func, eb->cancel_baton,
                      scratch_pool));

  return SVN_NO_ERROR;
}
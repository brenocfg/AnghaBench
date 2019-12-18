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
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct file_baton {struct edit_baton* edit_baton; void* ambiently_excluded; } ;
struct edit_baton {int /*<<< orphan*/  db; int /*<<< orphan*/  anchor_abspath; } ;
struct dir_baton {scalar_t__ ambient_depth; struct edit_baton* edit_baton; scalar_t__ ambiently_excluded; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (char const*) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* TRUE ; 
 int /*<<< orphan*/  ambient_read_info (scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 struct file_baton* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ svn_depth_empty ; 
 scalar_t__ svn_depth_unknown ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_unknown ; 
 scalar_t__ svn_wc__db_status_excluded ; 
 scalar_t__ svn_wc__db_status_not_present ; 
 scalar_t__ svn_wc__db_status_server_excluded ; 

__attribute__((used)) static svn_error_t *
make_file_baton(struct file_baton **f_p,
                struct dir_baton *pb,
                const char *path,
                svn_boolean_t added,
                apr_pool_t *pool)
{
  struct file_baton *f = apr_pcalloc(pool, sizeof(*f));
  struct edit_baton *eb = pb->edit_baton;
  svn_wc__db_status_t status;
  svn_node_kind_t kind;
  const char *abspath;

  SVN_ERR_ASSERT(path);

  if (pb->ambiently_excluded)
    {
      f->ambiently_excluded = TRUE;
      *f_p = f;
      return SVN_NO_ERROR;
    }

  abspath = svn_dirent_join(eb->anchor_abspath, path, pool);

  if (!added)
    {
      SVN_ERR(ambient_read_info(&status, &kind, NULL,
                                eb->db, abspath, pool));
    }
  else
    {
      status = svn_wc__db_status_not_present;
      kind = svn_node_unknown;
    }

  if (pb->ambient_depth == svn_depth_empty)
    {
      /* This is not a depth upgrade, and the parent directory is
         depth==empty.  So if the parent doesn't
         already have an entry for the file, then the parent
         doesn't want to hear about the file at all. */

      if (status == svn_wc__db_status_not_present
          || status == svn_wc__db_status_server_excluded
          || status == svn_wc__db_status_excluded
          || kind == svn_node_unknown)
        {
          f->ambiently_excluded = TRUE;
          *f_p = f;
          return SVN_NO_ERROR;
        }
    }

  /* If pb->ambient_depth == svn_depth_unknown we are pulling
     in new nodes */
  if (pb->ambient_depth != svn_depth_unknown
      && status == svn_wc__db_status_excluded)
    {
      f->ambiently_excluded = TRUE;
      *f_p = f;
      return SVN_NO_ERROR;
    }

  f->edit_baton = pb->edit_baton;

  *f_p = f;
  return SVN_NO_ERROR;
}
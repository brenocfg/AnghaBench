#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct edit_baton {TYPE_1__* wrapped_editor; int /*<<< orphan*/  db; int /*<<< orphan*/  anchor_abspath; } ;
struct dir_baton {scalar_t__ ambient_depth; int /*<<< orphan*/  wrapped_baton; scalar_t__ ambiently_excluded; struct edit_baton* edit_baton; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_2__ {int /*<<< orphan*/ * (* delete_entry ) (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  ambient_read_info (scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_depth_immediates ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_unknown ; 
 scalar_t__ svn_wc__db_status_excluded ; 
 scalar_t__ svn_wc__db_status_not_present ; 
 scalar_t__ svn_wc__db_status_server_excluded ; 

__attribute__((used)) static svn_error_t *
delete_entry(const char *path,
             svn_revnum_t base_revision,
             void *parent_baton,
             apr_pool_t *pool)
{
  struct dir_baton *pb = parent_baton;
  struct edit_baton *eb = pb->edit_baton;

  if (pb->ambiently_excluded)
    return SVN_NO_ERROR;

  if (pb->ambient_depth < svn_depth_immediates)
    {
      /* If the entry we want to delete doesn't exist, that's OK.
         It's probably an old server that doesn't understand
         depths. */
      svn_node_kind_t kind;
      svn_wc__db_status_t status;
      const char *abspath;

      abspath = svn_dirent_join(eb->anchor_abspath, path, pool);

      SVN_ERR(ambient_read_info(&status, &kind, NULL,
                                eb->db, abspath, pool));

      if (kind == svn_node_unknown
          || status == svn_wc__db_status_not_present
          || status == svn_wc__db_status_excluded
          || status == svn_wc__db_status_server_excluded)
        return SVN_NO_ERROR;
    }

  return eb->wrapped_editor->delete_entry(path, base_revision,
                                          pb->wrapped_baton, pool);
}
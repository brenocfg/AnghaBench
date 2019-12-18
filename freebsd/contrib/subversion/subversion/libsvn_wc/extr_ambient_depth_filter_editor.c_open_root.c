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
typedef  int /*<<< orphan*/  svn_depth_t ;
struct edit_baton {int /*<<< orphan*/  wrapped_edit_baton; TYPE_1__* wrapped_editor; int /*<<< orphan*/  anchor_abspath; int /*<<< orphan*/  db; int /*<<< orphan*/ * target; } ;
struct dir_baton {int /*<<< orphan*/  wrapped_baton; int /*<<< orphan*/  ambient_depth; scalar_t__ ambiently_excluded; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_2__ {int /*<<< orphan*/ * (* open_root ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  ambient_read_info (scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_dir_baton (struct dir_baton**,int /*<<< orphan*/ *,struct edit_baton*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_unknown ; 
 scalar_t__ svn_wc__db_status_excluded ; 
 scalar_t__ svn_wc__db_status_not_present ; 
 scalar_t__ svn_wc__db_status_server_excluded ; 

__attribute__((used)) static svn_error_t *
open_root(void *edit_baton,
          svn_revnum_t base_revision,
          apr_pool_t *pool,
          void **root_baton)
{
  struct edit_baton *eb = edit_baton;
  struct dir_baton *b;

  SVN_ERR(make_dir_baton(&b, NULL, eb, NULL, FALSE, pool));
  *root_baton = b;

  if (b->ambiently_excluded)
    return SVN_NO_ERROR;

  if (! *eb->target)
    {
      /* For an update with a NULL target, this is equivalent to open_dir(): */
      svn_node_kind_t kind;
      svn_wc__db_status_t status;
      svn_depth_t depth;

      /* Read the depth from the entry. */
      SVN_ERR(ambient_read_info(&status, &kind, &depth,
                                eb->db, eb->anchor_abspath,
                                pool));

      if (kind != svn_node_unknown
          && status != svn_wc__db_status_not_present
          && status != svn_wc__db_status_excluded
          && status != svn_wc__db_status_server_excluded)
        {
          b->ambient_depth = depth;
        }
    }

  return eb->wrapped_editor->open_root(eb->wrapped_edit_baton, base_revision,
                                       pool, &b->wrapped_baton);
}
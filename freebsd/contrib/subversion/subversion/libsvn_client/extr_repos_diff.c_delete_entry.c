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
typedef  int svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct edit_baton {int /*<<< orphan*/  revision; int /*<<< orphan*/  ra_session; int /*<<< orphan*/  pool; } ;
struct dir_baton {scalar_t__ skip_children; struct edit_baton* edit_baton; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  diff_deleted_dir (char const*,struct dir_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  diff_deleted_file (char const*,struct dir_baton*,int /*<<< orphan*/ *) ; 
#define  svn_node_dir 129 
#define  svn_node_file 128 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_check_path (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
delete_entry(const char *path,
             svn_revnum_t base_revision,
             void *parent_baton,
             apr_pool_t *pool)
{
  struct dir_baton *pb = parent_baton;
  struct edit_baton *eb = pb->edit_baton;
  svn_node_kind_t kind;
  apr_pool_t *scratch_pool;

  /* Process skips. */
  if (pb->skip_children)
    return SVN_NO_ERROR;

  scratch_pool = svn_pool_create(eb->pool);

  /* We need to know if this is a directory or a file */
  SVN_ERR(svn_ra_check_path(eb->ra_session, path, eb->revision, &kind,
                            scratch_pool));

  switch (kind)
    {
    case svn_node_file:
      {
        SVN_ERR(diff_deleted_file(path, pb, scratch_pool));
        break;
      }
    case svn_node_dir:
      {
        SVN_ERR(diff_deleted_dir(path, pb, scratch_pool));
        break;
      }
    default:
      break;
    }

  svn_pool_destroy(scratch_pool);

  return SVN_NO_ERROR;
}
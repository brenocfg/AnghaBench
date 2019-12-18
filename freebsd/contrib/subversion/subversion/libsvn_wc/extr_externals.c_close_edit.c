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
struct edit_baton {int /*<<< orphan*/  notify_baton; int /*<<< orphan*/  notify_func; int /*<<< orphan*/ * target_revision; int /*<<< orphan*/  repos_uuid; int /*<<< orphan*/  repos_root_url; int /*<<< orphan*/  new_repos_relpath; int /*<<< orphan*/  local_abspath; int /*<<< orphan*/  db; int /*<<< orphan*/  iprops; int /*<<< orphan*/  file_closed; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_depth_infinity ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__db_op_bump_revisions_post_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
close_edit(void *edit_baton,
           apr_pool_t *pool)
{
  struct edit_baton *eb = edit_baton;

  if (!eb->file_closed)
    {
      apr_hash_t *wcroot_iprops = NULL;
      /* The file wasn't updated, but its url or revision might have...
         e.g. switch between branches for relative externals.

         Just bump the information as that is just as expensive as
         investigating when we should and shouldn't update it...
         and avoid hard to debug edge cases */

      if (eb->iprops)
        {
          wcroot_iprops = apr_hash_make(pool);
          svn_hash_sets(wcroot_iprops, eb->local_abspath, eb->iprops);
        }

      SVN_ERR(svn_wc__db_op_bump_revisions_post_update(eb->db,
                                                       eb->local_abspath,
                                                       svn_depth_infinity,
                                                       eb->new_repos_relpath,
                                                       eb->repos_root_url,
                                                       eb->repos_uuid,
                                                       *eb->target_revision,
                                                       apr_hash_make(pool)
                                                       /* exclude_relpaths */,
                                                       wcroot_iprops,
                                                       TRUE /* empty update */,
                                                       eb->notify_func,
                                                       eb->notify_baton,
                                                       pool));
    }

  return SVN_NO_ERROR;
}
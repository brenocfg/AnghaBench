#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* svn_wc_status_func4_t ) (void*,char const*,TYPE_1__*,int /*<<< orphan*/ *) ;
struct TYPE_8__ {int /*<<< orphan*/  repos_node_status; } ;
struct TYPE_9__ {TYPE_1__ s; scalar_t__ has_descendants; } ;
typedef  TYPE_2__ svn_wc__internal_status_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  scalar_t__ svn_boolean_t ;
struct status_baton {void* real_status_baton; int /*<<< orphan*/  (* real_status_func ) (void*,char const*,TYPE_1__*,int /*<<< orphan*/ *) ;} ;
struct edit_baton {void* status_baton; int /*<<< orphan*/  (* status_func ) (void*,char const*,TYPE_1__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  get_all; int /*<<< orphan*/  no_ignore; int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; int /*<<< orphan*/  wb; int /*<<< orphan*/ * ignores; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 TYPE_2__* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_dir_status (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char const*,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (void*,char const*,TYPE_1__*,int /*<<< orphan*/ *),void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ is_sendable_status (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_deleted (void*,char const*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (void*,char const*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_depth_infinity ; 
 int /*<<< orphan*/  svn_depth_unknown ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_status_deleted ; 

__attribute__((used)) static svn_error_t *
handle_statii(struct edit_baton *eb,
              const char *dir_repos_root_url,
              const char *dir_repos_relpath,
              const char *dir_repos_uuid,
              apr_hash_t *statii,
              svn_boolean_t dir_was_deleted,
              svn_depth_t depth,
              apr_pool_t *pool)
{
  const apr_array_header_t *ignores = eb->ignores;
  apr_hash_index_t *hi;
  apr_pool_t *iterpool = svn_pool_create(pool);
  svn_wc_status_func4_t status_func = eb->status_func;
  void *status_baton = eb->status_baton;
  struct status_baton sb;

  if (dir_was_deleted)
    {
      sb.real_status_func = eb->status_func;
      sb.real_status_baton = eb->status_baton;
      status_func = mark_deleted;
      status_baton = &sb;
    }

  /* Loop over all the statii still in our hash, handling each one. */
  for (hi = apr_hash_first(pool, statii); hi; hi = apr_hash_next(hi))
    {
      const char *local_abspath = apr_hash_this_key(hi);
      svn_wc__internal_status_t *status = apr_hash_this_val(hi);

      /* Clear the subpool. */
      svn_pool_clear(iterpool);

      /* Now, handle the status.  We don't recurse for svn_depth_immediates
         because we already have the subdirectories' statii. */
      if (status->has_descendants
          && (depth == svn_depth_unknown
              || depth == svn_depth_infinity))
        {
          SVN_ERR(get_dir_status(&eb->wb,
                                 local_abspath, TRUE,
                                 dir_repos_root_url, dir_repos_relpath,
                                 dir_repos_uuid,
                                 NULL,
                                 NULL /* dirent */,
                                 ignores, depth, eb->get_all, eb->no_ignore,
                                 status_func, status_baton,
                                 eb->cancel_func, eb->cancel_baton,
                                 iterpool));
        }
      if (dir_was_deleted)
        status->s.repos_node_status = svn_wc_status_deleted;
      if (is_sendable_status(status, eb->no_ignore, eb->get_all))
        SVN_ERR((eb->status_func)(eb->status_baton, local_abspath, &status->s,
                                  iterpool));
    }

  /* Destroy the subpool. */
  svn_pool_destroy(iterpool);

  return SVN_NO_ERROR;
}
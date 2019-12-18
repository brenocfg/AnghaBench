#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_lock_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_12__ {scalar_t__ kind; } ;
typedef  TYPE_1__ svn_dirent_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/ * (* svn_client_info_receiver2_t ) (void*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_client_info2_t ;
struct TYPE_13__ {int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/ * (* cancel_func ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ svn_client_ctx_t ;
struct TYPE_14__ {int /*<<< orphan*/  rev; } ;
typedef  TYPE_3__ svn_client__pathrev_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIRENT_FIELDS ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 TYPE_1__* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build_info_from_dirent (int /*<<< orphan*/ **,TYPE_1__*,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ) ; 
 char* svn_client__pathrev_fspath (TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_client__pathrev_join_relpath (TYPE_3__ const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_depth_files ; 
 int /*<<< orphan*/  svn_depth_immediates ; 
 int /*<<< orphan*/  svn_depth_infinity ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_get_dir2 (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* svn_relpath_join (char const*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
push_dir_info(svn_ra_session_t *ra_session,
              const svn_client__pathrev_t *pathrev,
              const char *dir,
              svn_client_info_receiver2_t receiver,
              void *receiver_baton,
              svn_depth_t depth,
              svn_client_ctx_t *ctx,
              apr_hash_t *locks,
              apr_pool_t *pool)
{
  apr_hash_t *tmpdirents;
  apr_hash_index_t *hi;
  apr_pool_t *subpool = svn_pool_create(pool);

  SVN_ERR(svn_ra_get_dir2(ra_session, &tmpdirents, NULL, NULL,
                          dir, pathrev->rev, DIRENT_FIELDS, pool));

  for (hi = apr_hash_first(pool, tmpdirents); hi; hi = apr_hash_next(hi))
    {
      const char *path, *fs_path;
      svn_lock_t *lock;
      svn_client_info2_t *info;
      const char *name = apr_hash_this_key(hi);
      svn_dirent_t *the_ent = apr_hash_this_val(hi);
      svn_client__pathrev_t *child_pathrev;

      svn_pool_clear(subpool);

      if (ctx->cancel_func)
        SVN_ERR(ctx->cancel_func(ctx->cancel_baton));

      path = svn_relpath_join(dir, name, subpool);
      child_pathrev = svn_client__pathrev_join_relpath(pathrev, name, subpool);
      fs_path = svn_client__pathrev_fspath(child_pathrev, subpool);

      lock = svn_hash_gets(locks, fs_path);

      SVN_ERR(build_info_from_dirent(&info, the_ent, lock, child_pathrev,
                                     subpool));

      if (depth >= svn_depth_immediates
          || (depth == svn_depth_files && the_ent->kind == svn_node_file))
        {
          SVN_ERR(receiver(receiver_baton, path, info, subpool));
        }

      if (depth == svn_depth_infinity && the_ent->kind == svn_node_dir)
        {
          SVN_ERR(push_dir_info(ra_session, child_pathrev, path,
                                receiver, receiver_baton,
                                depth, ctx, locks, subpool));
        }
    }

  svn_pool_destroy(subpool);

  return SVN_NO_ERROR;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
struct TYPE_8__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_client__pathrev_t ;
struct repos_move_info {int dummy; } ;
struct copy_info {int /*<<< orphan*/  node_kind; int /*<<< orphan*/  copyfrom_rev; int /*<<< orphan*/  copyto_path; int /*<<< orphan*/  copyfrom_path; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_FS_NOT_FOUND ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  add_new_move (struct repos_move_info**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* find_yca (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rev_below (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 

__attribute__((used)) static svn_error_t *
find_related_move(struct repos_move_info **move,
                  struct copy_info *copy,
                  const char *deleted_repos_relpath,
                  svn_revnum_t deleted_rev,
                  const char *author,
                  apr_hash_t *moved_paths,
                  const char *repos_root_url,
                  const char *repos_uuid,
                  svn_client_ctx_t *ctx,
                  svn_ra_session_t *ra_session,
                  apr_pool_t *result_pool,
                  apr_pool_t *scratch_pool)
{
  svn_client__pathrev_t *yca_loc;
  svn_error_t *err;

  *move = NULL;
  err = find_yca(&yca_loc, copy->copyfrom_path, copy->copyfrom_rev,
                 deleted_repos_relpath, rev_below(deleted_rev),
                 repos_root_url, repos_uuid, ra_session, ctx,
                 scratch_pool, scratch_pool);
  if (err)
    {
      if (err->apr_err == SVN_ERR_FS_NOT_FOUND)
        {
          svn_error_clear(err);
          yca_loc = NULL;
        }
      else
        return svn_error_trace(err);
    }

  if (yca_loc)
    SVN_ERR(add_new_move(move, deleted_repos_relpath,
                         copy->copyto_path, copy->copyfrom_rev,
                         copy->node_kind, deleted_rev, author,
                         moved_paths, ra_session, repos_root_url,
                         result_pool, scratch_pool));

  return SVN_NO_ERROR;
}
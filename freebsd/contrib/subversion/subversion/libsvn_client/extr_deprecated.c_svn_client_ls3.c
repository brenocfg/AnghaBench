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
typedef  int /*<<< orphan*/  svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct ls_baton {int /*<<< orphan*/ * pool; int /*<<< orphan*/ * locks; int /*<<< orphan*/ * dirents; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_DIRENT_ALL ; 
 void* apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  store_dirent ; 
 int /*<<< orphan*/ * svn_client_list (char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ls_baton*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client_ls3(apr_hash_t **dirents,
               apr_hash_t **locks,
               const char *path_or_url,
               const svn_opt_revision_t *peg_revision,
               const svn_opt_revision_t *revision,
               svn_boolean_t recurse,
               svn_client_ctx_t *ctx,
               apr_pool_t *pool)
{
  struct ls_baton lb;

  *dirents = lb.dirents = apr_hash_make(pool);
  if (locks)
    *locks = lb.locks = apr_hash_make(pool);
  lb.pool = pool;

  return svn_client_list(path_or_url, peg_revision, revision, recurse,
                         SVN_DIRENT_ALL, locks != NULL,
                         store_dirent, &lb, ctx, pool);
}
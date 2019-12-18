#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  new_filename; int /*<<< orphan*/  old_filename; } ;
typedef  TYPE_1__ svn_patch_t ;
typedef  int /*<<< orphan*/  svn_patch_file_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_patch_abspath (char**,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_get_wc_root (char const**,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_diff_close_patch_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_diff_open_patch_file (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_diff_parse_next_patch (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client_shelf_get_paths(apr_hash_t **affected_paths,
                           const char *name,
                           const char *local_abspath,
                           svn_client_ctx_t *ctx,
                           apr_pool_t *result_pool,
                           apr_pool_t *scratch_pool)
{
  const char *wc_root_abspath;
  char *patch_abspath;
  svn_patch_file_t *patch_file;
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);
  apr_hash_t *paths = apr_hash_make(result_pool);

  SVN_ERR(svn_client_get_wc_root(&wc_root_abspath,
                                 local_abspath, ctx, scratch_pool, scratch_pool));
  SVN_ERR(get_patch_abspath(&patch_abspath, name, wc_root_abspath,
                            ctx, scratch_pool, scratch_pool));
  SVN_ERR(svn_diff_open_patch_file(&patch_file, patch_abspath, result_pool));

  while (1)
    {
      svn_patch_t *patch;

      svn_pool_clear(iterpool);
      SVN_ERR(svn_diff_parse_next_patch(&patch, patch_file,
                                        FALSE /*reverse*/,
                                        FALSE /*ignore_whitespace*/,
                                        iterpool, iterpool));
      if (! patch)
        break;
      svn_hash_sets(paths,
                    apr_pstrdup(result_pool, patch->old_filename),
                    apr_pstrdup(result_pool, patch->new_filename));
    }
  SVN_ERR(svn_diff_close_patch_file(patch_file, iterpool));
  svn_pool_destroy(iterpool);

  *affected_paths = paths;
  return SVN_NO_ERROR;
}
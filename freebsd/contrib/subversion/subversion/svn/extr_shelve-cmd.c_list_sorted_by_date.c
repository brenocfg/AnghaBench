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
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  compare_shelved_patch_infos_by_mtime ; 
 int /*<<< orphan*/  svn_client_shelves_list (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_sort__hash (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
list_sorted_by_date(apr_array_header_t **list,
                    const char *local_abspath,
                    svn_client_ctx_t *ctx,
                    apr_pool_t *scratch_pool)
{
  apr_hash_t *shelved_patch_infos;

  SVN_ERR(svn_client_shelves_list(&shelved_patch_infos, local_abspath,
                                  ctx, scratch_pool, scratch_pool));
  *list = svn_sort__hash(shelved_patch_infos,
                         compare_shelved_patch_infos_by_mtime,
                         scratch_pool);
  return SVN_NO_ERROR;
}
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
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_client_list_func2_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;
struct TYPE_9__ {int /*<<< orphan*/  nelts; } ;
typedef  TYPE_2__ apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 TYPE_1__* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_external_items (TYPE_2__*,char const*,TYPE_2__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_parse_externals_description3 (TYPE_2__**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
list_externals(apr_hash_t *externals,
               const apr_array_header_t *patterns,
               svn_depth_t depth,
               apr_uint32_t dirent_fields,
               svn_boolean_t fetch_locks,
               svn_client_list_func2_t list_func,
               void *baton,
               svn_client_ctx_t *ctx,
               apr_pool_t *scratch_pool)
{
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);
  apr_hash_index_t *hi;

  for (hi = apr_hash_first(scratch_pool, externals);
       hi;
       hi = apr_hash_next(hi))
    {
      const char *externals_parent_url = apr_hash_this_key(hi);
      svn_string_t *externals_desc = apr_hash_this_val(hi);
      apr_array_header_t *external_items;

      svn_pool_clear(iterpool);

      SVN_ERR(svn_wc_parse_externals_description3(&external_items,
                                                  externals_parent_url,
                                                  externals_desc->data,
                                                  FALSE, iterpool));

      if (! external_items->nelts)
        continue;

      SVN_ERR(list_external_items(external_items, externals_parent_url,
                                  patterns, depth, dirent_fields,
                                  fetch_locks, list_func, baton, ctx,
                                  iterpool));

    }
  svn_pool_destroy(iterpool);

  return SVN_NO_ERROR;
}
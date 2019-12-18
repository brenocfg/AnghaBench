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
typedef  int /*<<< orphan*/  svn_memcache_t ;
typedef  int /*<<< orphan*/  svn_membuffer_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cache__t ;
typedef  int /*<<< orphan*/  svn_cache__serialize_func_t ;
typedef  int /*<<< orphan*/ * svn_cache__error_handler_t ;
typedef  int /*<<< orphan*/  svn_cache__deserialize_func_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  scalar_t__ apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_ssize_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SVN_CACHE__MEMBUFFER_DEFAULT_PRIORITY ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  init_callbacks (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__create_inprocess (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__create_membuffer_cache (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__create_memcache (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__create_null (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * warn_and_continue_on_cache_errors ; 
 int /*<<< orphan*/ * warn_and_fail_on_cache_errors ; 

__attribute__((used)) static svn_error_t *
create_cache(svn_cache__t **cache_p,
             svn_memcache_t *memcache,
             svn_membuffer_t *membuffer,
             apr_int64_t pages,
             apr_int64_t items_per_page,
             svn_cache__serialize_func_t serializer,
             svn_cache__deserialize_func_t deserializer,
             apr_ssize_t klen,
             const char *prefix,
             apr_uint32_t priority,
             svn_boolean_t has_namespace,
             svn_fs_t *fs,
             svn_boolean_t no_handler,
             svn_boolean_t dummy_cache,
             apr_pool_t *result_pool,
             apr_pool_t *scratch_pool)
{
  svn_cache__error_handler_t error_handler = no_handler
                                           ? NULL
                                           : warn_and_fail_on_cache_errors;
  if (priority == 0)
    priority = SVN_CACHE__MEMBUFFER_DEFAULT_PRIORITY;

  if (dummy_cache)
    {
      SVN_ERR(svn_cache__create_null(cache_p, prefix, result_pool));
    }
  else if (memcache)
    {
      SVN_ERR(svn_cache__create_memcache(cache_p, memcache,
                                         serializer, deserializer, klen,
                                         prefix, result_pool));
      error_handler = no_handler
                    ? NULL
                    : warn_and_continue_on_cache_errors;
    }
  else if (membuffer)
    {
      /* We assume caches with namespaces to be relatively short-lived,
       * i.e. their data will not be needed after a while. */
      SVN_ERR(svn_cache__create_membuffer_cache(
                cache_p, membuffer, serializer, deserializer,
                klen, prefix, priority, FALSE, has_namespace,
                result_pool, scratch_pool));
    }
  else if (pages)
    {
      SVN_ERR(svn_cache__create_inprocess(
                cache_p, serializer, deserializer, klen, pages,
                items_per_page, FALSE, prefix, result_pool));
    }
  else
    {
      SVN_ERR(svn_cache__create_null(cache_p, prefix, result_pool));
    }

  SVN_ERR(init_callbacks(*cache_p, fs, error_handler, result_pool));

  return SVN_NO_ERROR;
}
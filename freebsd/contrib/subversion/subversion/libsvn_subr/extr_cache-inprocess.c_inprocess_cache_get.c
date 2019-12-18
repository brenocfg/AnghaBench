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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_3__ {int /*<<< orphan*/ * (* deserialize_func ) (void**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ inprocess_cache_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_MUTEX__WITH_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  inprocess_cache_get_internal (char**,int /*<<< orphan*/ *,TYPE_1__*,void const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (void**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
inprocess_cache_get(void **value_p,
                    svn_boolean_t *found,
                    void *cache_void,
                    const void *key,
                    apr_pool_t *result_pool)
{
  inprocess_cache_t *cache = cache_void;

  if (key)
    {
      char* buffer;
      apr_size_t size;

      SVN_MUTEX__WITH_LOCK(cache->mutex,
                           inprocess_cache_get_internal(&buffer,
                                                        &size,
                                                        cache,
                                                        key,
                                                        result_pool));
      /* deserialize the buffer content. Usually, this will directly
         modify the buffer content directly. */
      *found = (buffer != NULL);
      if (!buffer || !size)
        *value_p = NULL;
      else
        return cache->deserialize_func(value_p, buffer, size, result_pool);
    }
  else
    {
      *value_p = NULL;
      *found = FALSE;
    }

  return SVN_NO_ERROR;
}
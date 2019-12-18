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
struct TYPE_3__ {scalar_t__ klen; } ;
typedef  TYPE_1__ inprocess_cache_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ APR_HASH_KEY_STRING ; 
 void const* apr_pmemdup (int /*<<< orphan*/ *,void const*,scalar_t__) ; 
 void const* apr_pstrdup (int /*<<< orphan*/ *,void const*) ; 

__attribute__((used)) static const void *
duplicate_key(inprocess_cache_t *cache,
              const void *key,
              apr_pool_t *pool)
{
  if (cache->klen == APR_HASH_KEY_STRING)
    return apr_pstrdup(pool, key);
  else
    return apr_pmemdup(pool, key, cache->klen);
}
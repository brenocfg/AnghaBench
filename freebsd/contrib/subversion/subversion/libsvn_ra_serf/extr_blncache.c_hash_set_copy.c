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
typedef  scalar_t__ apr_ssize_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 scalar_t__ APR_HASH_KEY_STRING ; 
 int /*<<< orphan*/  apr_hash_pool_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,void const*) ; 
 int /*<<< orphan*/  apr_pmemdup (int /*<<< orphan*/ ,void const*,scalar_t__) ; 
 scalar_t__ strlen (void const*) ; 

__attribute__((used)) static void
hash_set_copy(apr_hash_t *hash,
              const void *key,
              apr_ssize_t klen,
              const void *val)
{
  if (klen == APR_HASH_KEY_STRING)
    klen = strlen(key);
  apr_hash_set(hash, apr_pmemdup(apr_hash_pool_get(hash), key, klen),
               klen, val);
}
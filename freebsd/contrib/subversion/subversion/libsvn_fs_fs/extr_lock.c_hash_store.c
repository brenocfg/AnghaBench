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
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 scalar_t__ APR_HASH_KEY_STRING ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ *,char const*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  svn_string_ncreate (char const*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
hash_store(apr_hash_t *hash,
           const char *key,
           apr_ssize_t key_len,
           const char *value,
           apr_ssize_t value_len,
           apr_pool_t *pool)
{
  if (! (key && value))
    return;
  if (value_len == APR_HASH_KEY_STRING)
    value_len = strlen(value);
  apr_hash_set(hash, key, key_len,
               svn_string_ncreate(value, value_len, pool));
}
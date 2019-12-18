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
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 scalar_t__ apr_hash_this_key (int /*<<< orphan*/ *) ; 
 scalar_t__ apr_hash_this_val (int /*<<< orphan*/ *) ; 
 char** apr_palloc (int /*<<< orphan*/ *,int) ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char*,char const*,char const*) ; 

__attribute__((used)) static const char **
env_from_env_hash(apr_hash_t *env_hash,
                  apr_pool_t *result_pool,
                  apr_pool_t *scratch_pool)
{
  apr_hash_index_t *hi;
  const char **env;
  const char **envp;

  if (!env_hash)
    return NULL;

  env = apr_palloc(result_pool,
                   sizeof(const char *) * (apr_hash_count(env_hash) + 1));
  envp = env;
  for (hi = apr_hash_first(scratch_pool, env_hash); hi; hi = apr_hash_next(hi))
    {
      *envp = apr_psprintf(result_pool, "%s=%s",
                           (const char *)apr_hash_this_key(hi),
                           (const char *)apr_hash_this_val(hi));
      envp++;
    }
  *envp = NULL;

  return env;
}
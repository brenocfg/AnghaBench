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
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct parse_hooks_env_option_baton {char const* section; int /*<<< orphan*/ * hooks_env; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_pool_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_boolean_t
parse_hooks_env_option(const char *name, const char *value,
                       void *baton, apr_pool_t *pool)
{
  struct parse_hooks_env_option_baton *bo = baton;
  apr_pool_t *result_pool = apr_hash_pool_get(bo->hooks_env);
  apr_hash_t *hook_env;

  hook_env = svn_hash_gets(bo->hooks_env, bo->section);
  if (hook_env == NULL)
    {
      hook_env = apr_hash_make(result_pool);
      svn_hash_sets(bo->hooks_env, apr_pstrdup(result_pool, bo->section),
                    hook_env);
    }
  svn_hash_sets(hook_env, apr_pstrdup(result_pool, name),
                apr_pstrdup(result_pool, value));

  return TRUE;
}
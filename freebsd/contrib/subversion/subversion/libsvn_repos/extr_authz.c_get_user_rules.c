#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* filtered; int /*<<< orphan*/  full; int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ svn_authz_t ;
struct TYPE_8__ {int /*<<< orphan*/  global_rights; int /*<<< orphan*/ * root; int /*<<< orphan*/  lookup_state; int /*<<< orphan*/ * user; int /*<<< orphan*/ * repository; int /*<<< orphan*/ * pool; } ;
typedef  TYPE_2__ authz_user_rules_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_2__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  create_lookup_state (int /*<<< orphan*/ *) ; 
 scalar_t__ matches_filtered_tree (TYPE_2__*,char const*,char const*) ; 
 int /*<<< orphan*/  svn_authz__get_global_rights (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static authz_user_rules_t *
get_user_rules(svn_authz_t *authz,
               const char *repos_name,
               const char *user)
{
  apr_pool_t *pool;

  /* Search our cache for a suitable previously filtered tree. */
  if (authz->filtered)
    {
      /* Is this a suitable filtered tree? */
      if (matches_filtered_tree(authz->filtered, repos_name, user))
        return authz->filtered;

      /* Drop the old filtered tree before creating a new one. */
      svn_pool_destroy(authz->filtered->pool);
      authz->filtered = NULL;
    }

  /* Global cache lookup.  Filter the full model only if necessary. */
  pool = svn_pool_create(authz->pool);

  /* Write a new entry. */
  authz->filtered = apr_palloc(pool, sizeof(*authz->filtered));
  authz->filtered->pool = pool;
  authz->filtered->repository = apr_pstrdup(pool, repos_name);
  authz->filtered->user = user ? apr_pstrdup(pool, user) : NULL;
  authz->filtered->lookup_state = create_lookup_state(pool);
  authz->filtered->root = NULL;

  svn_authz__get_global_rights(&authz->filtered->global_rights,
                               authz->full, user, repos_name);

  return authz->filtered;
}
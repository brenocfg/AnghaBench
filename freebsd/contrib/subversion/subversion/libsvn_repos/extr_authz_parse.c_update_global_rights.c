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
typedef  int /*<<< orphan*/  authz_rights_t ;
struct TYPE_3__ {int /*<<< orphan*/  per_repos_rights; int /*<<< orphan*/  any_repos_rights; int /*<<< orphan*/  all_repos_rights; } ;
typedef  TYPE_1__ authz_global_rights_t ;
typedef  int /*<<< orphan*/  authz_access_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUTHZ_ANY_REPOSITORY ; 
 int /*<<< orphan*/  apr_hash_pool_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_palloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  init_rights (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_rights (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
update_global_rights(authz_global_rights_t *gr,
                     const char *repos,
                     authz_access_t access)
{
  update_rights(&gr->all_repos_rights, access);
  if (0 == strcmp(repos, AUTHZ_ANY_REPOSITORY))
    update_rights(&gr->any_repos_rights, access);
  else
    {
      authz_rights_t *rights = svn_hash_gets(gr->per_repos_rights, repos);
      if (rights)
        update_rights(rights, access);
      else
        {
          rights = apr_palloc(apr_hash_pool_get(gr->per_repos_rights),
                              sizeof(*rights));
          init_rights(rights);
          update_rights(rights, access);
          svn_hash_sets(gr->per_repos_rights, repos, rights);
        }
    }
}
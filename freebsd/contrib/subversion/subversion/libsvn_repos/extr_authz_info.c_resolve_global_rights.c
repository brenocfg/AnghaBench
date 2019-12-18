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
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  authz_rights_t ;
struct TYPE_3__ {int /*<<< orphan*/  any_repos_rights; int /*<<< orphan*/  per_repos_rights; } ;
typedef  TYPE_1__ authz_global_rights_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUTHZ_ANY_REPOSITORY ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  combine_rights (int /*<<< orphan*/ *,int /*<<< orphan*/  const* const,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static svn_boolean_t
resolve_global_rights(authz_rights_t *rights_p,
                      const authz_global_rights_t *global_rights,
                      const char *repos)
{
  if (0 == strcmp(repos, AUTHZ_ANY_REPOSITORY))
    {
      /* Return the accumulated rights that are not repository-specific. */
      *rights_p = global_rights->any_repos_rights;
      return TRUE;
    }
  else
    {
      /* Check if we have explicit rights for this repository. */
      const authz_rights_t *const rights =
        svn_hash_gets(global_rights->per_repos_rights, repos);

      if (rights)
        {
          combine_rights(rights_p, rights, &global_rights->any_repos_rights);
          return TRUE;
        }
    }

  /* Fall-through: return the rights defined for "any" repository
     because this user has no specific rules for this specific REPOS. */
  *rights_p = global_rights->any_repos_rights;
  return FALSE;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_9__ {void* max_access; void* min_access; } ;
typedef  TYPE_1__ authz_rights_t ;
typedef  int /*<<< orphan*/  authz_global_rights_t ;
struct TYPE_10__ {int /*<<< orphan*/  const authn_rights; scalar_t__ has_authn_rights; int /*<<< orphan*/  user_rights; int /*<<< orphan*/  const anon_rights; scalar_t__ has_anon_rights; } ;
typedef  TYPE_2__ authz_full_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUTHZ_ANONYMOUS_USER ; 
 int /*<<< orphan*/  FALSE ; 
 void* authz_access_none ; 
 int /*<<< orphan*/  combine_rights (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  resolve_global_rights (TYPE_1__*,int /*<<< orphan*/  const*,char const*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ ,char const*) ; 

svn_boolean_t
svn_authz__get_global_rights(authz_rights_t *rights_p,
                             const authz_full_t *authz,
                             const char *user, const char *repos)
{
  if (!user || 0 == strcmp(user, AUTHZ_ANONYMOUS_USER))
    {
      /* Check if we have explicit rights for anonymous access. */
      if (authz->has_anon_rights)
        return resolve_global_rights(rights_p, &authz->anon_rights, repos);
    }
  else
    {
      /* Check if we have explicit rights for this user. */
      const authz_global_rights_t *const user_rights =
        svn_hash_gets(authz->user_rights, user);

      if (user_rights)
        {
          svn_boolean_t explicit
            = resolve_global_rights(rights_p, user_rights, repos);

          /* Rights given to _any_ authenticated user may apply, too. */
          if (authz->has_authn_rights)
            {
              authz_rights_t authn;
              explicit |= resolve_global_rights(&authn, &authz->authn_rights,
                                                repos);
              combine_rights(rights_p, rights_p, &authn);
            }
          return explicit;
        }

      /* Check if we have explicit rights for authenticated access. */
      if (authz->has_authn_rights)
        return resolve_global_rights(rights_p, &authz->authn_rights, repos);
    }

  /* Fall-through: return the implicit rights, i.e., none. */
  rights_p->min_access = authz_access_none;
  rights_p->max_access = authz_access_none;
  return FALSE;
}
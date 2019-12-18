#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int svn_repos_authz_access_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
struct TYPE_11__ {TYPE_2__* filtered; } ;
typedef  TYPE_3__ svn_authz_t ;
struct TYPE_9__ {int const min_access; int const max_access; } ;
struct TYPE_12__ {int /*<<< orphan*/  lookup_state; int /*<<< orphan*/  root; TYPE_1__ global_rights; } ;
typedef  TYPE_4__ authz_user_rules_t ;
typedef  int authz_access_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_10__ {int /*<<< orphan*/  root; int /*<<< orphan*/  lookup_state; } ;

/* Variables and functions */
 char const* AUTHZ_ANY_REPOSITORY ; 
 int FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int TRUE ; 
 int authz_access_read_flag ; 
 int authz_access_write_flag ; 
 int /*<<< orphan*/  filter_tree (TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_4__* get_user_rules (TYPE_3__*,char const*,char const*) ; 
 char* init_lockup_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int lookup (int /*<<< orphan*/ ,char const*,int const,int,int /*<<< orphan*/ *) ; 
 int svn_authz_read ; 
 int svn_authz_recursive ; 
 int svn_authz_write ; 

svn_error_t *
svn_repos_authz_check_access(svn_authz_t *authz, const char *repos_name,
                             const char *path, const char *user,
                             svn_repos_authz_access_t required_access,
                             svn_boolean_t *access_granted,
                             apr_pool_t *pool)
{
  const authz_access_t required =
    ((required_access & svn_authz_read ? authz_access_read_flag : 0)
     | (required_access & svn_authz_write ? authz_access_write_flag : 0));

  /* Pick or create the suitable pre-filtered path rule tree. */
  authz_user_rules_t *rules = get_user_rules(
      authz,
      (repos_name ? repos_name : AUTHZ_ANY_REPOSITORY),
      user);

  /* In many scenarios, users have uniform access to a repository
   * (blanket access or no access at all).
   *
   * In these cases, don't bother creating or consulting the filtered tree.
   */
  if ((rules->global_rights.min_access & required) == required)
    {
      *access_granted = TRUE;
      return SVN_NO_ERROR;
    }

  if ((rules->global_rights.max_access & required) != required)
    {
      *access_granted = FALSE;
      return SVN_NO_ERROR;
    }

  /* No specific path given, i.e. looking for anywhere in the tree? */
  if (!path)
    {
      *access_granted =
        ((rules->global_rights.max_access & required) == required);
      return SVN_NO_ERROR;
    }

  /* Rules tree lookup */

  /* Did we already filter the data model? */
  if (!rules->root)
    SVN_ERR(filter_tree(authz, pool));

  /* Re-use previous lookup results, if possible. */
  path = init_lockup_state(authz->filtered->lookup_state,
                           authz->filtered->root, path);

  /* Sanity check. */
  SVN_ERR_ASSERT(path[0] == '/');

  /* Determine the granted access for the requested path.
   * PATH does not need to be normalized for lockup(). */
  *access_granted = lookup(rules->lookup_state, path, required,
                           !!(required_access & svn_authz_recursive), pool);

  return SVN_NO_ERROR;
}
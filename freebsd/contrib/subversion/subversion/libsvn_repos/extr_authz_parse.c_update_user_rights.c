#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  authz_global_rights_t ;
struct TYPE_4__ {int /*<<< orphan*/  repos; } ;
struct TYPE_5__ {TYPE_1__ rule; } ;
typedef  TYPE_2__ authz_acl_t ;
typedef  int /*<<< orphan*/  authz_access_t ;
typedef  int /*<<< orphan*/  apr_ssize_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ svn_authz__get_acl_access (int /*<<< orphan*/ *,TYPE_2__ const* const,char const* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_global_rights (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
update_user_rights(void *baton,
                   const void *key,
                   apr_ssize_t klen,
                   void *value,
                   apr_pool_t *scratch_pool)
{
  const authz_acl_t *const acl = baton;
  const char *const user = key;
  authz_global_rights_t *const gr = value;
  authz_access_t access;
  svn_boolean_t has_access =
    svn_authz__get_acl_access(&access, acl, user, acl->rule.repos);

  if (has_access)
    update_global_rights(gr, acl->rule.repos, access);
  return SVN_NO_ERROR;
}
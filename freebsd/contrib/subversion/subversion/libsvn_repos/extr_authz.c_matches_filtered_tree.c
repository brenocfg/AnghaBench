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
typedef  int svn_boolean_t ;
struct TYPE_3__ {int /*<<< orphan*/ * repository; int /*<<< orphan*/ * user; } ;
typedef  TYPE_1__ authz_user_rules_t ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_boolean_t
matches_filtered_tree(const authz_user_rules_t *authz,
                      const char *repos_name,
                      const char *user)
{
  /* Does the user match? */
  if (user)
    {
      if (authz->user == NULL || strcmp(user, authz->user))
        return FALSE;
    }
  else if (authz->user != NULL)
    return FALSE;

  /* Does the repository match as well? */
  return strcmp(repos_name, authz->repository) == 0;
}
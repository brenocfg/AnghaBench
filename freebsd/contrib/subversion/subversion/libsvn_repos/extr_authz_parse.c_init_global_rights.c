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
struct TYPE_3__ {char const* user; int /*<<< orphan*/  per_repos_rights; int /*<<< orphan*/  any_repos_rights; int /*<<< orphan*/  all_repos_rights; } ;
typedef  TYPE_1__ authz_global_rights_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_rights (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
init_global_rights(authz_global_rights_t *gr, const char *user,
                   apr_pool_t *result_pool)
{
  gr->user = user;
  init_rights(&gr->all_repos_rights);
  init_rights(&gr->any_repos_rights);
  gr->per_repos_rights = apr_hash_make(result_pool);
}
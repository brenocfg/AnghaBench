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
struct TYPE_3__ {int /*<<< orphan*/  rev; int /*<<< orphan*/  url; int /*<<< orphan*/  repos_root_url; } ;
typedef  TYPE_1__ svn_client__pathrev_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char const* apr_psprintf (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 
 char* svn_uri_skip_ancestor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
pathrev_str(const svn_client__pathrev_t *pathrev,
            apr_pool_t *pool)
{
  const char *rrpath
    = svn_uri_skip_ancestor(pathrev->repos_root_url, pathrev->url, pool);

  return apr_psprintf(pool, "^/%s@%ld", rrpath, pathrev->rev);
}
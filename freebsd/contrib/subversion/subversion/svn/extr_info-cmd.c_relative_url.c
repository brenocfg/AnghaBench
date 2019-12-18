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
struct TYPE_3__ {int /*<<< orphan*/  URL; int /*<<< orphan*/  repos_root_URL; } ;
typedef  TYPE_1__ svn_client_info2_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_VA_NULL ; 
 char const* apr_pstrcat (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_path_uri_encode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_uri_skip_ancestor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char*
relative_url(const svn_client_info2_t *info, apr_pool_t *pool)
{
  return apr_pstrcat(pool, "^/",
                     svn_path_uri_encode(
                         svn_uri_skip_ancestor(info->repos_root_URL,
                                               info->URL, pool),
                         pool), SVN_VA_NULL);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_2__ {int /*<<< orphan*/  server; } ;
typedef  TYPE_1__ authz_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * authz_check_access (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_authz_read ; 

__attribute__((used)) static svn_error_t *authz_check_access_cb(svn_boolean_t *allowed,
                                          svn_fs_root_t *root,
                                          const char *path,
                                          void *baton,
                                          apr_pool_t *pool)
{
  authz_baton_t *sb = baton;

  return authz_check_access(allowed, path, svn_authz_read,
                            sb->server, pool);
}
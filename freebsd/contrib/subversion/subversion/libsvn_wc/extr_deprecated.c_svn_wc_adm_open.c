#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_wc_adm_open3 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_adm_open(svn_wc_adm_access_t **adm_access,
                svn_wc_adm_access_t *associated,
                const char *path,
                svn_boolean_t write_lock,
                svn_boolean_t tree_lock,
                apr_pool_t *pool)
{
  return svn_wc_adm_open3(adm_access, associated, path, write_lock,
                          (tree_lock ? -1 : 0), NULL, NULL, pool);
}
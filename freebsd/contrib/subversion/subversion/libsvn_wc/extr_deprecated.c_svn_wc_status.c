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
typedef  int /*<<< orphan*/  svn_wc_status_t ;
typedef  int /*<<< orphan*/  svn_wc_status2_t ;
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_wc_status2 (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_status(svn_wc_status_t **status,
              const char *path,
              svn_wc_adm_access_t *adm_access,
              apr_pool_t *pool)
{
  svn_wc_status2_t *stat2;

  SVN_ERR(svn_wc_status2(&stat2, path, adm_access, pool));
  *status = (svn_wc_status_t *) stat2;
  return SVN_NO_ERROR;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_5__ {int /*<<< orphan*/  baseline_info; } ;
typedef  TYPE_1__ svn_ra_serf__blncache_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {int /*<<< orphan*/  revision; int /*<<< orphan*/  bc_url; } ;
typedef  TYPE_2__ baseline_info_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_hash_gets (int /*<<< orphan*/ ,char const*) ; 

svn_error_t *
svn_ra_serf__blncache_get_baseline_info(const char **bc_url_p,
                                        svn_revnum_t *revision_p,
                                        svn_ra_serf__blncache_t *blncache,
                                        const char *baseline_url,
                                        apr_pool_t *pool)
{
  baseline_info_t *info = svn_hash_gets(blncache->baseline_info, baseline_url);
  if (info)
    {
      *bc_url_p = apr_pstrdup(pool, info->bc_url);
      *revision_p = info->revision;
    }
  else
    {
      *bc_url_p = NULL;
      *revision_p = SVN_INVALID_REVNUM;
    }

  return SVN_NO_ERROR;
}
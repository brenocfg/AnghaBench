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
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_ra_callbacks2_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_ra_open4 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *svn_ra_open3(svn_ra_session_t **session_p,
                          const char *repos_URL,
                          const char *uuid,
                          const svn_ra_callbacks2_t *callbacks,
                          void *callback_baton,
                          apr_hash_t *config,
                          apr_pool_t *pool)
{
  return svn_ra_open4(session_p, NULL, repos_URL, uuid,
                      callbacks, callback_baton, config, pool);
}
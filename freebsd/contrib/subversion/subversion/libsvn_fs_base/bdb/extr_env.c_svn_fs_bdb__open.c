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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  bdb_env_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_MUTEX__WITH_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  bdb_cache_lock ; 
 int /*<<< orphan*/  svn_fs_bdb__open_internal (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_bdb__open(bdb_env_baton_t **bdb_batonp, const char *path,
                 u_int32_t flags, int mode,
                 apr_pool_t *pool)
{
  SVN_MUTEX__WITH_LOCK(bdb_cache_lock,
                       svn_fs_bdb__open_internal(bdb_batonp,
                                                 path,
                                                 flags,
                                                 mode,
                                                 pool));

  return SVN_NO_ERROR;
}
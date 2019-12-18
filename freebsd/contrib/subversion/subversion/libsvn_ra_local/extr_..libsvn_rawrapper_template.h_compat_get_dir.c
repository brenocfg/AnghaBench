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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_2__ {int /*<<< orphan*/ * (* get_dir ) (void*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_DIRENT_ALL ; 
 TYPE_1__ VTBL ; 
 int /*<<< orphan*/ * stub1 (void*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *compat_get_dir(void *session_baton,
                                   const char *path,
                                   svn_revnum_t revision,
                                   apr_hash_t **dirents,
                                   svn_revnum_t *fetched_rev,
                                   apr_hash_t **props,
                                   apr_pool_t *pool)
{
  return VTBL.get_dir(session_baton, dirents, fetched_rev, props,
                      path, revision, SVN_DIRENT_ALL, pool);
}
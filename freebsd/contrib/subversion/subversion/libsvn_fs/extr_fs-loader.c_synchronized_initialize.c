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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_2__ {int /*<<< orphan*/ * next; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  apr_pool_cleanup_null ; 
 int /*<<< orphan*/  apr_pool_cleanup_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ base_defn ; 
 int /*<<< orphan*/  common_pool ; 
 int /*<<< orphan*/  common_pool_lock ; 
 int /*<<< orphan*/  svn_mutex__init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uninit ; 

__attribute__((used)) static svn_error_t *
synchronized_initialize(void *baton, apr_pool_t *pool)
{
  common_pool = svn_pool_create(pool);
  base_defn.next = NULL;
  SVN_ERR(svn_mutex__init(&common_pool_lock, TRUE, common_pool));

  /* ### This won't work if POOL is NULL and libsvn_fs is loaded as a DSO
     ### (via libsvn_ra_local say) since the global common_pool will live
     ### longer than the DSO, which gets unloaded when the pool used to
     ### load it is cleared, and so when the handler runs it will refer to
     ### a function that no longer exists.  libsvn_ra_local attempts to
     ### work around this by explicitly calling svn_fs_initialize. */
  apr_pool_cleanup_register(common_pool, NULL, uninit, apr_pool_cleanup_null);
  return SVN_NO_ERROR;
}
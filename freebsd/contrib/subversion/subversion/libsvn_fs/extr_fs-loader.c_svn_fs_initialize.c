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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  common_pool_initialized ; 
 int /*<<< orphan*/  svn_atomic__init_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dso_initialize2 () ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronized_initialize ; 

svn_error_t *
svn_fs_initialize(apr_pool_t *pool)
{
#if defined(SVN_USE_DSO) && APR_HAS_DSO
  /* Ensure that DSO subsystem is initialized early as possible if
     we're going to use it. */
  SVN_ERR(svn_dso_initialize2());
#endif
  /* Protect against multiple calls. */
  return svn_error_trace(svn_atomic__init_once(&common_pool_initialized,
                                               synchronized_initialize,
                                               NULL, pool));
}
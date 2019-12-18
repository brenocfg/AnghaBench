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
 int /*<<< orphan*/  create_thread_pool ; 
 int /*<<< orphan*/  svn_atomic__init_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_pool_initialized ; 

svn_error_t *
svn_fs_x__batch_fsync_init(apr_pool_t *owning_pool)
{
  /* Protect against multiple calls. */
  return svn_error_trace(svn_atomic__init_once(&thread_pool_initialized,
                                               create_thread_pool,
                                               NULL, owning_pool));
}
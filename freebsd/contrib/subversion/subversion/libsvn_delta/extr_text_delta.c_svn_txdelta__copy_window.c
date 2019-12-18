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
typedef  int /*<<< orphan*/  svn_txdelta_window_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_txdelta_window_dup (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

svn_txdelta_window_t *
svn_txdelta__copy_window(const svn_txdelta_window_t *window,
                         apr_pool_t *pool)
{
  return svn_txdelta_window_dup(window, pool);
}
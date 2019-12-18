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
struct notify_baton {int /*<<< orphan*/  conflict_stats; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_cl__print_conflict_stats (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_cl__notifier_print_conflict_stats(void *baton, apr_pool_t *scratch_pool)
{
  struct notify_baton *nb = baton;

  SVN_ERR(svn_cl__print_conflict_stats(nb->conflict_stats, scratch_pool));
  return SVN_NO_ERROR;
}
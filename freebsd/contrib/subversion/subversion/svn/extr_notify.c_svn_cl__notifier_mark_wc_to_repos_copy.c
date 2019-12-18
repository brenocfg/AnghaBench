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
struct notify_baton {int /*<<< orphan*/  is_wc_to_repos_copy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 

svn_error_t *
svn_cl__notifier_mark_wc_to_repos_copy(void *baton)
{
  struct notify_baton *nb = baton;

  nb->is_wc_to_repos_copy = TRUE;
  return SVN_NO_ERROR;
}
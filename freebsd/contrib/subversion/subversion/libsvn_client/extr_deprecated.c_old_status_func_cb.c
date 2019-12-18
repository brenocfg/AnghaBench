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
typedef  int /*<<< orphan*/  svn_wc_status_t ;
typedef  int /*<<< orphan*/  svn_wc_status2_t ;
struct old_status_func_cb_baton {int /*<<< orphan*/  original_baton; int /*<<< orphan*/  (* original_func ) (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void old_status_func_cb(void *baton,
                               const char *path,
                               svn_wc_status2_t *status)
{
  struct old_status_func_cb_baton *b = baton;
  svn_wc_status_t *stat = (svn_wc_status_t *) status;

  b->original_func(b->original_baton, path, stat);
}
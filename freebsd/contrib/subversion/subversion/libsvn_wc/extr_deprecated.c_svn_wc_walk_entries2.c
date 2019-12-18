#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  found_entry; } ;
typedef  TYPE_1__ svn_wc_entry_callbacks_t ;
struct TYPE_6__ {int /*<<< orphan*/  handle_error; int /*<<< orphan*/  found_entry; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ svn_wc_entry_callbacks2_t ;
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_depth_infinity ; 
 int /*<<< orphan*/  svn_wc__walker_default_error_handler ; 
 int /*<<< orphan*/ * svn_wc_walk_entries3 (char const*,int /*<<< orphan*/ *,TYPE_2__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_walk_entries2(const char *path,
                     svn_wc_adm_access_t *adm_access,
                     const svn_wc_entry_callbacks_t *walk_callbacks,
                     void *walk_baton,
                     svn_boolean_t show_hidden,
                     svn_cancel_func_t cancel_func,
                     void *cancel_baton,
                     apr_pool_t *pool)
{
  svn_wc_entry_callbacks2_t walk_cb2 = { 0 };
  walk_cb2.found_entry = walk_callbacks->found_entry;
  walk_cb2.handle_error = svn_wc__walker_default_error_handler;
  return svn_wc_walk_entries3(path, adm_access,
                              &walk_cb2, walk_baton, svn_depth_infinity,
                              show_hidden, cancel_func, cancel_baton, pool);
}
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
typedef  int /*<<< orphan*/  svn_wc_notify_state_t ;
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_wc_merge_props2 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_merge_prop_diffs(svn_wc_notify_state_t *state,
                        const char *path,
                        svn_wc_adm_access_t *adm_access,
                        const apr_array_header_t *propchanges,
                        svn_boolean_t base_merge,
                        svn_boolean_t dry_run,
                        apr_pool_t *pool)
{
  /* NOTE: Here, we use implementation knowledge.  The public
     svn_wc_merge_props2 doesn't allow NULL as baseprops argument, but we know
     that it works. */
  return svn_wc_merge_props2(state, path, adm_access, NULL, propchanges,
                             base_merge, dry_run, NULL, NULL, pool);
}
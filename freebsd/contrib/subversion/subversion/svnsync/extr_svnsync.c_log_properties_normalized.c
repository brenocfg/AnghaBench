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
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_PREFIX ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  svn_cmdline_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static svn_error_t *
log_properties_normalized(int normalized_rev_props_count,
                          int normalized_node_props_count,
                          apr_pool_t *pool)
{
  if (normalized_rev_props_count > 0 || normalized_node_props_count > 0)
    SVN_ERR(svn_cmdline_printf(pool,
                               _("NOTE: Normalized %s* properties "
                                 "to LF line endings (%d rev-props, "
                                 "%d node-props).\n"),
                               SVN_PROP_PREFIX,
                               normalized_rev_props_count,
                               normalized_node_props_count));
  return SVN_NO_ERROR;
}
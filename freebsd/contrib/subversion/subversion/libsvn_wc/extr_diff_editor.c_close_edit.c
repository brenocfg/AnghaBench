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
struct edit_baton_t {int /*<<< orphan*/  pool; int /*<<< orphan*/  depth; int /*<<< orphan*/  anchor_abspath; int /*<<< orphan*/  root_opened; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  walk_local_nodes_diff (struct edit_baton_t*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
close_edit(void *edit_baton,
           apr_pool_t *pool)
{
  struct edit_baton_t *eb = edit_baton;

  if (!eb->root_opened)
    {
      SVN_ERR(walk_local_nodes_diff(eb,
                                    eb->anchor_abspath,
                                    "",
                                    eb->depth,
                                    NULL /* compared */,
                                    NULL /* No parent_baton */,
                                    eb->pool));
    }

  return SVN_NO_ERROR;
}
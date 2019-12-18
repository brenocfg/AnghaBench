#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  make_absolute (int /*<<< orphan*/  const**,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_children_of_working_node (int /*<<< orphan*/  const**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__node_get_children_of_working_node(const apr_array_header_t **children,
                                          svn_wc_context_t *wc_ctx,
                                          const char *dir_abspath,
                                          apr_pool_t *result_pool,
                                          apr_pool_t *scratch_pool)
{
  const apr_array_header_t *child_names;

  SVN_ERR(svn_wc__db_read_children_of_working_node(&child_names,
                                                   wc_ctx->db, dir_abspath,
                                                   scratch_pool, scratch_pool));
  make_absolute(children, dir_abspath, child_names, result_pool);
  return SVN_NO_ERROR;
}
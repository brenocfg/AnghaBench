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
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_node_none ; 
 scalar_t__ svn_node_symlink ; 
 int /*<<< orphan*/  svn_wc__db_read_kind (scalar_t__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_read_kind2(svn_node_kind_t *kind,
                  svn_wc_context_t *wc_ctx,
                  const char *local_abspath,
                  svn_boolean_t show_deleted,
                  svn_boolean_t show_hidden,
                  apr_pool_t *scratch_pool)
{
  svn_node_kind_t db_kind;

  SVN_ERR(svn_wc__db_read_kind(&db_kind,
                               wc_ctx->db, local_abspath,
                               TRUE,
                               show_deleted,
                               show_hidden,
                               scratch_pool));

  if (db_kind == svn_node_dir)
    *kind = svn_node_dir;
  else if (db_kind == svn_node_file || db_kind == svn_node_symlink)
    *kind = svn_node_file;
  else
    *kind = svn_node_none;

  return SVN_NO_ERROR;
}
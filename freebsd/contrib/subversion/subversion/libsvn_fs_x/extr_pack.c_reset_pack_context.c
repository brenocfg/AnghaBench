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
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {int /*<<< orphan*/  info_pool; int /*<<< orphan*/  paths; int /*<<< orphan*/  reps_file; int /*<<< orphan*/  reps; int /*<<< orphan*/  references; int /*<<< orphan*/  path_order; int /*<<< orphan*/  rev_offsets; int /*<<< orphan*/  dir_props_file; int /*<<< orphan*/  dir_props; int /*<<< orphan*/  file_props_file; int /*<<< orphan*/  file_props; int /*<<< orphan*/  changes_file; int /*<<< orphan*/  changes; } ;
typedef  TYPE_1__ pack_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_array_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_trunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_prefix_tree__create (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
reset_pack_context(pack_context_t *context,
                   apr_pool_t *scratch_pool)
{
  apr_array_clear(context->changes);
  SVN_ERR(svn_io_file_trunc(context->changes_file, 0, scratch_pool));
  apr_array_clear(context->file_props);
  SVN_ERR(svn_io_file_trunc(context->file_props_file, 0, scratch_pool));
  apr_array_clear(context->dir_props);
  SVN_ERR(svn_io_file_trunc(context->dir_props_file, 0, scratch_pool));

  apr_array_clear(context->rev_offsets);
  apr_array_clear(context->path_order);
  apr_array_clear(context->references);
  apr_array_clear(context->reps);
  SVN_ERR(svn_io_file_trunc(context->reps_file, 0, scratch_pool));

  svn_pool_clear(context->info_pool);
  context->paths = svn_prefix_tree__create(context->info_pool);

  return SVN_NO_ERROR;
}
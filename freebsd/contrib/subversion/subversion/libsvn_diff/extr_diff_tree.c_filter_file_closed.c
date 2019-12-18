#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {struct filter_tree_baton_t* baton; } ;
typedef  TYPE_1__ svn_diff_tree_processor_t ;
typedef  int /*<<< orphan*/  svn_diff_source_t ;
struct filter_tree_baton_t {TYPE_2__* processor; int /*<<< orphan*/  prefix_relpath; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* file_closed ) (char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,void*,TYPE_2__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,void*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 char* svn_relpath_skip_ancestor (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static svn_error_t *
filter_file_closed(const char *relpath,
                   const svn_diff_source_t *left_source,
                   const svn_diff_source_t *right_source,
                   void *file_baton,
                   const svn_diff_tree_processor_t *processor,
                   apr_pool_t *scratch_pool)
{
  struct filter_tree_baton_t *fb = processor->baton;

  relpath = svn_relpath_skip_ancestor(fb->prefix_relpath, relpath);
  assert(relpath != NULL); /* Driver error */

  SVN_ERR(fb->processor->file_closed(relpath,
                                     left_source,
                                     right_source,
                                     file_baton,
                                     fb->processor,
                                     scratch_pool));

  return SVN_NO_ERROR;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* dir_closed ) (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,void*,TYPE_1__ const*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ svn_diff_tree_processor_t ;
typedef  int /*<<< orphan*/  svn_diff_source_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,void*,TYPE_1__ const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
default_dir_added(const char *relpath,
                  const svn_diff_source_t *copyfrom_source,
                  const svn_diff_source_t *right_source,
                  /*const*/ apr_hash_t *copyfrom_props,
                  /*const*/ apr_hash_t *right_props,
                  void *dir_baton,
                  const svn_diff_tree_processor_t *processor,
                  apr_pool_t *scratch_pool)
{
  SVN_ERR(processor->dir_closed(relpath, NULL, right_source,
                                dir_baton, processor,
                                scratch_pool));

  return SVN_NO_ERROR;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {TYPE_3__* baton; } ;
typedef  TYPE_2__ svn_diff_tree_processor_t ;
struct merge_dir_baton_t {int dummy; } ;
struct TYPE_8__ {TYPE_1__* target; } ;
typedef  TYPE_3__ merge_cmd_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_6__ {int /*<<< orphan*/  abspath; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  record_skip (TYPE_3__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct merge_dir_baton_t*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_unknown ; 
 int /*<<< orphan*/  svn_wc_notify_skip ; 
 int /*<<< orphan*/  svn_wc_notify_state_missing ; 

__attribute__((used)) static svn_error_t *
merge_node_absent(const char *relpath,
                  void *dir_baton,
                  const svn_diff_tree_processor_t *processor,
                  apr_pool_t *scratch_pool)
{
  merge_cmd_baton_t *merge_b = processor->baton;
  struct merge_dir_baton_t *db = dir_baton;

  const char *local_abspath = svn_dirent_join(merge_b->target->abspath,
                                              relpath, scratch_pool);

  SVN_ERR(record_skip(merge_b, local_abspath, svn_node_unknown,
                      svn_wc_notify_skip, svn_wc_notify_state_missing,
                      db, scratch_pool));

  return SVN_NO_ERROR;
}
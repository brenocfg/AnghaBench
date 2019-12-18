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
struct TYPE_3__ {int /*<<< orphan*/  operation; int /*<<< orphan*/  old_symlink_bit; int /*<<< orphan*/  old_executable_bit; } ;
typedef  TYPE_1__ svn_patch_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  enum parse_state { ____Placeholder_parse_state } parse_state ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int STRLEN_LITERAL (char*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  parse_git_mode_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int state_git_tree_seen ; 
 int /*<<< orphan*/  svn_diff_op_deleted ; 

__attribute__((used)) static svn_error_t *
git_deleted_file(enum parse_state *new_state, char *line, svn_patch_t *patch,
                 apr_pool_t *result_pool, apr_pool_t *scratch_pool)
{
  SVN_ERR(parse_git_mode_bits(&patch->old_executable_bit,
                              &patch->old_symlink_bit,
                              line + STRLEN_LITERAL("deleted file mode ")));

  patch->operation = svn_diff_op_deleted;

  /* Filename already retrieved from diff --git header. */

  *new_state = state_git_tree_seen;
  return SVN_NO_ERROR;
}
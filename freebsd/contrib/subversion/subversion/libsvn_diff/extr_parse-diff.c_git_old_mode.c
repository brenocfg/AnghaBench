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
struct TYPE_3__ {scalar_t__ old_executable_bit; int /*<<< orphan*/  old_symlink_bit; } ;
typedef  TYPE_1__ svn_patch_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  enum parse_state { ____Placeholder_parse_state } parse_state ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int STRLEN_LITERAL (char*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  parse_git_mode_bits (scalar_t__*,int /*<<< orphan*/ *,char*) ; 
 int state_old_mode_seen ; 
 scalar_t__ svn_tristate_unknown ; 

__attribute__((used)) static svn_error_t *
git_old_mode(enum parse_state *new_state, char *line, svn_patch_t *patch,
             apr_pool_t *result_pool, apr_pool_t *scratch_pool)
{
  SVN_ERR(parse_git_mode_bits(&patch->old_executable_bit,
                              &patch->old_symlink_bit,
                              line + STRLEN_LITERAL("old mode ")));

#ifdef SVN_DEBUG
  /* If this assert trips, the "old mode" is neither ...644 nor ...755 . */
  SVN_ERR_ASSERT(patch->old_executable_bit != svn_tristate_unknown);
#endif

  *new_state = state_old_mode_seen;
  return SVN_NO_ERROR;
}
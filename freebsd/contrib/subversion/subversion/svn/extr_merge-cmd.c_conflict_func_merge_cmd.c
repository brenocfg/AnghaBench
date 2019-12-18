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
typedef  int /*<<< orphan*/  svn_wc_conflict_result_t ;
struct TYPE_3__ {int /*<<< orphan*/  kind; int /*<<< orphan*/  local_abspath; } ;
typedef  TYPE_1__ svn_wc_conflict_description2_t ;
typedef  scalar_t__ svn_wc_conflict_choice_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct conflict_func_merge_cmd_baton {int accept_which; int /*<<< orphan*/  conflict_stats; int /*<<< orphan*/  path_prefix; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
#define  svn_cl__accept_base 139 
#define  svn_cl__accept_edit 138 
#define  svn_cl__accept_invalid 137 
#define  svn_cl__accept_launch 136 
#define  svn_cl__accept_mine_conflict 135 
#define  svn_cl__accept_mine_full 134 
#define  svn_cl__accept_postpone 133 
#define  svn_cl__accept_recommended 132 
#define  svn_cl__accept_theirs_conflict 131 
#define  svn_cl__accept_theirs_full 130 
#define  svn_cl__accept_unspecified 129 
#define  svn_cl__accept_working 128 
 int /*<<< orphan*/  svn_cl__conflict_stats_resolved (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 char* svn_cl__local_style_skip_ancestor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc_conflict_choose_base ; 
 scalar_t__ svn_wc_conflict_choose_merged ; 
 scalar_t__ svn_wc_conflict_choose_mine_conflict ; 
 scalar_t__ svn_wc_conflict_choose_mine_full ; 
 scalar_t__ svn_wc_conflict_choose_postpone ; 
 scalar_t__ svn_wc_conflict_choose_theirs_conflict ; 
 scalar_t__ svn_wc_conflict_choose_theirs_full ; 
 int /*<<< orphan*/ * svn_wc_create_conflict_result (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
conflict_func_merge_cmd(svn_wc_conflict_result_t **result,
                        const svn_wc_conflict_description2_t *desc,
                        void *baton,
                        apr_pool_t *result_pool,
                        apr_pool_t *scratch_pool)
{
  struct conflict_func_merge_cmd_baton *b = baton;
  svn_wc_conflict_choice_t choice;

  switch (b->accept_which)
    {
    case svn_cl__accept_postpone:
    case svn_cl__accept_invalid:
    case svn_cl__accept_unspecified:
    case svn_cl__accept_recommended:
      /* Postpone or no valid --accept option, postpone the conflict. */
      choice = svn_wc_conflict_choose_postpone;
      break;
    case svn_cl__accept_base:
      choice = svn_wc_conflict_choose_base;
      break;
    case svn_cl__accept_working:
      choice = svn_wc_conflict_choose_merged;
      break;
    case svn_cl__accept_mine_conflict:
      choice = svn_wc_conflict_choose_mine_conflict;
      break;
    case svn_cl__accept_theirs_conflict:
      choice = svn_wc_conflict_choose_theirs_conflict;
      break;
    case svn_cl__accept_mine_full:
      choice = svn_wc_conflict_choose_mine_full;
      break;
    case svn_cl__accept_theirs_full:
      choice = svn_wc_conflict_choose_theirs_full;
      break;
    case svn_cl__accept_edit:
    case svn_cl__accept_launch:
      /* The 'edit' and 'launch' options used to be valid in Subversion 1.9 but
       * we can't support these options for the purposes of this callback. */
      choice = svn_wc_conflict_choose_postpone;
      break;
    }

  *result = svn_wc_create_conflict_result(choice, NULL, result_pool);

  /* If we are resolving a conflict, adjust the summary of conflicts. */
  if (choice != svn_wc_conflict_choose_postpone)
    {
      const char *local_path;

      local_path = svn_cl__local_style_skip_ancestor(b->path_prefix,
                                                     desc->local_abspath,
                                                     scratch_pool);
      svn_cl__conflict_stats_resolved(b->conflict_stats, local_path,
                                      desc->kind);
    }

  return SVN_NO_ERROR;
}
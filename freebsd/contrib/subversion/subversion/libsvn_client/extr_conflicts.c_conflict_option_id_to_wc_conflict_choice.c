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
typedef  int /*<<< orphan*/  svn_wc_conflict_choice_t ;
typedef  int svn_client_conflict_option_id_t ;

/* Variables and functions */
#define  svn_client_conflict_option_base_text 136 
#define  svn_client_conflict_option_incoming_text 135 
#define  svn_client_conflict_option_incoming_text_where_conflicted 134 
#define  svn_client_conflict_option_merged_text 133 
#define  svn_client_conflict_option_postpone 132 
#define  svn_client_conflict_option_undefined 131 
#define  svn_client_conflict_option_unspecified 130 
#define  svn_client_conflict_option_working_text 129 
#define  svn_client_conflict_option_working_text_where_conflicted 128 
 int /*<<< orphan*/  svn_wc_conflict_choose_base ; 
 int /*<<< orphan*/  svn_wc_conflict_choose_merged ; 
 int /*<<< orphan*/  svn_wc_conflict_choose_mine_conflict ; 
 int /*<<< orphan*/  svn_wc_conflict_choose_mine_full ; 
 int /*<<< orphan*/  svn_wc_conflict_choose_postpone ; 
 int /*<<< orphan*/  svn_wc_conflict_choose_theirs_conflict ; 
 int /*<<< orphan*/  svn_wc_conflict_choose_theirs_full ; 
 int /*<<< orphan*/  svn_wc_conflict_choose_undefined ; 
 int /*<<< orphan*/  svn_wc_conflict_choose_unspecified ; 

__attribute__((used)) static svn_wc_conflict_choice_t
conflict_option_id_to_wc_conflict_choice(
  svn_client_conflict_option_id_t option_id)
{

  switch (option_id)
    {
      case svn_client_conflict_option_undefined:
        return svn_wc_conflict_choose_undefined;

      case svn_client_conflict_option_postpone:
        return svn_wc_conflict_choose_postpone;

      case svn_client_conflict_option_base_text:
        return svn_wc_conflict_choose_base;

      case svn_client_conflict_option_incoming_text:
        return svn_wc_conflict_choose_theirs_full;

      case svn_client_conflict_option_working_text:
        return svn_wc_conflict_choose_mine_full;

      case svn_client_conflict_option_incoming_text_where_conflicted:
        return svn_wc_conflict_choose_theirs_conflict;

      case svn_client_conflict_option_working_text_where_conflicted:
        return svn_wc_conflict_choose_mine_conflict;

      case svn_client_conflict_option_merged_text:
        return svn_wc_conflict_choose_merged;

      case svn_client_conflict_option_unspecified:
        return svn_wc_conflict_choose_unspecified;

      default:
        break;
    }

  return svn_wc_conflict_choose_undefined;
}
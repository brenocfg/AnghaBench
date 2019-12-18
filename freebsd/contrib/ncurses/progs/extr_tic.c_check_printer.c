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
typedef  int /*<<< orphan*/  TERMTYPE ;

/* Variables and functions */
 int /*<<< orphan*/  ANDMISSING (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAIRED (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enter_doublewide_mode ; 
 int /*<<< orphan*/  enter_italics_mode ; 
 int /*<<< orphan*/  enter_leftward_mode ; 
 int /*<<< orphan*/  enter_micro_mode ; 
 int /*<<< orphan*/  enter_shadow_mode ; 
 int /*<<< orphan*/  enter_subscript_mode ; 
 int /*<<< orphan*/  enter_superscript_mode ; 
 int /*<<< orphan*/  enter_upward_mode ; 
 int /*<<< orphan*/  exit_doublewide_mode ; 
 int /*<<< orphan*/  exit_italics_mode ; 
 int /*<<< orphan*/  exit_leftward_mode ; 
 int /*<<< orphan*/  exit_micro_mode ; 
 int /*<<< orphan*/  exit_shadow_mode ; 
 int /*<<< orphan*/  exit_subscript_mode ; 
 int /*<<< orphan*/  exit_superscript_mode ; 
 int /*<<< orphan*/  exit_upward_mode ; 
 int /*<<< orphan*/  micro_down ; 
 int /*<<< orphan*/  micro_left ; 
 int /*<<< orphan*/  micro_right ; 
 int /*<<< orphan*/  micro_up ; 
 int /*<<< orphan*/  parm_down_micro ; 
 int /*<<< orphan*/  parm_left_micro ; 
 int /*<<< orphan*/  parm_right_micro ; 
 int /*<<< orphan*/  parm_up_micro ; 
 int /*<<< orphan*/  set_bottom_margin ; 
 int /*<<< orphan*/  set_bottom_margin_parm ; 
 int /*<<< orphan*/  set_left_margin ; 
 int /*<<< orphan*/  set_left_margin_parm ; 
 int /*<<< orphan*/  set_right_margin ; 
 int /*<<< orphan*/  set_right_margin_parm ; 
 int /*<<< orphan*/  set_top_margin ; 
 int /*<<< orphan*/  set_top_margin_parm ; 
 int /*<<< orphan*/  start_char_set_def ; 
 int /*<<< orphan*/  stop_char_set_def ; 

__attribute__((used)) static void
check_printer(TERMTYPE *tp)
{
    PAIRED(enter_doublewide_mode, exit_doublewide_mode);
    PAIRED(enter_italics_mode, exit_italics_mode);
    PAIRED(enter_leftward_mode, exit_leftward_mode);
    PAIRED(enter_micro_mode, exit_micro_mode);
    PAIRED(enter_shadow_mode, exit_shadow_mode);
    PAIRED(enter_subscript_mode, exit_subscript_mode);
    PAIRED(enter_superscript_mode, exit_superscript_mode);
    PAIRED(enter_upward_mode, exit_upward_mode);

    ANDMISSING(start_char_set_def, stop_char_set_def);

    /* if we have a parameterized form, then the non-parameterized is easy */
    ANDMISSING(set_bottom_margin_parm, set_bottom_margin);
    ANDMISSING(set_left_margin_parm, set_left_margin);
    ANDMISSING(set_right_margin_parm, set_right_margin);
    ANDMISSING(set_top_margin_parm, set_top_margin);

    ANDMISSING(parm_down_micro, micro_down);
    ANDMISSING(parm_left_micro, micro_left);
    ANDMISSING(parm_right_micro, micro_right);
    ANDMISSING(parm_up_micro, micro_up);
}
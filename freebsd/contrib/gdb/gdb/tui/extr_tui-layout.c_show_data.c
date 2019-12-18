#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct tui_gen_win_info {int width; int /*<<< orphan*/  type; } ;
typedef  enum tui_win_type { ____Placeholder_tui_win_type } tui_win_type ;
typedef  enum tui_layout_type { ____Placeholder_tui_layout_type } tui_layout_type ;
struct TYPE_16__ {void* can_highlight; } ;
struct TYPE_13__ {void* has_locator; struct tui_gen_win_info* execution_info; } ;
struct TYPE_14__ {TYPE_2__ source_info; } ;
struct TYPE_15__ {TYPE_3__ detail; struct tui_gen_win_info generic; } ;
struct TYPE_12__ {int height; } ;
struct TYPE_11__ {TYPE_1__ generic; } ;

/* Variables and functions */
 int DISASSEM_WIN ; 
 int /*<<< orphan*/  DONT_BOX_WINDOW ; 
 int /*<<< orphan*/  EXEC_INFO_WIN ; 
 int /*<<< orphan*/  LOCATOR_WIN ; 
 int SRC_DATA_COMMAND ; 
 int SRC_WIN ; 
 void* TRUE ; 
 TYPE_10__* TUI_CMD_WIN ; 
 TYPE_8__* TUI_DATA_WIN ; 
 int /*<<< orphan*/  init_and_make_win (void**,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_gen_win_info (struct tui_gen_win_info*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  make_data_window (TYPE_8__**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_disasm_window (TYPE_4__**,int,int) ; 
 int /*<<< orphan*/  make_source_window (TYPE_4__**,int,int) ; 
 int /*<<< orphan*/  tui_add_to_source_windows (TYPE_4__*) ; 
 struct tui_gen_win_info* tui_locator_win_info_ptr () ; 
 int /*<<< orphan*/  tui_make_all_invisible () ; 
 int /*<<< orphan*/  tui_make_invisible (struct tui_gen_win_info*) ; 
 int /*<<< orphan*/  tui_make_visible (struct tui_gen_win_info*) ; 
 int /*<<< orphan*/  tui_set_current_layout_to (int) ; 
 int /*<<< orphan*/  tui_show_locator_content () ; 
 int tui_term_height () ; 
 int tui_term_width () ; 
 TYPE_4__** tui_win_list ; 

__attribute__((used)) static void
show_data (enum tui_layout_type new_layout)
{
  int total_height = (tui_term_height () - TUI_CMD_WIN->generic.height);
  int src_height, data_height;
  enum tui_win_type win_type;
  struct tui_gen_win_info * locator = tui_locator_win_info_ptr ();


  data_height = total_height / 2;
  src_height = total_height - data_height;
  tui_make_all_invisible ();
  tui_make_invisible (locator);
  make_data_window (&TUI_DATA_WIN, data_height, 0);
  TUI_DATA_WIN->can_highlight = TRUE;
  if (new_layout == SRC_DATA_COMMAND)
    win_type = SRC_WIN;
  else
    win_type = DISASSEM_WIN;
  if (tui_win_list[win_type] == NULL)
    {
      if (win_type == SRC_WIN)
	make_source_window (&tui_win_list[win_type], src_height, data_height - 1);
      else
	make_disasm_window (&tui_win_list[win_type], src_height, data_height - 1);
      init_and_make_win ((void **) & locator,
		       LOCATOR_WIN,
		       2 /* 1 */ ,
		       tui_term_width (),
		       0,
		       total_height - 1,
		       DONT_BOX_WINDOW);
    }
  else
    {
      init_gen_win_info (&tui_win_list[win_type]->generic,
		       tui_win_list[win_type]->generic.type,
		       src_height,
		       tui_win_list[win_type]->generic.width,
		   tui_win_list[win_type]->detail.source_info.execution_info->width,
		       data_height - 1);
      init_gen_win_info (tui_win_list[win_type]->detail.source_info.execution_info,
		       EXEC_INFO_WIN,
		       src_height,
		       3,
		       0,
		       data_height - 1);
      tui_make_visible (&tui_win_list[win_type]->generic);
      tui_make_visible (tui_win_list[win_type]->detail.source_info.execution_info);
      init_gen_win_info (locator,
		       LOCATOR_WIN,
		       2 /* 1 */ ,
		       tui_term_width (),
		       0,
		       total_height - 1);
    }
  tui_win_list[win_type]->detail.source_info.has_locator = TRUE;
  tui_make_visible (locator);
  tui_show_locator_content ();
  tui_add_to_source_windows (tui_win_list[win_type]);
  tui_set_current_layout_to (new_layout);
}
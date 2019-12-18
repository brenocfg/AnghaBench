#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  darrow; int /*<<< orphan*/  uarrow; int /*<<< orphan*/  check_selected; int /*<<< orphan*/  check; int /*<<< orphan*/  tag_key_selected; int /*<<< orphan*/  tag_key; int /*<<< orphan*/  tag_selected; int /*<<< orphan*/  tag; int /*<<< orphan*/  item_selected; int /*<<< orphan*/  item; int /*<<< orphan*/  menubox_border; int /*<<< orphan*/  menubox; int /*<<< orphan*/  position_indicator; int /*<<< orphan*/  searchbox_border; int /*<<< orphan*/  searchbox_title; int /*<<< orphan*/  searchbox; int /*<<< orphan*/  inputbox_border; int /*<<< orphan*/  inputbox; int /*<<< orphan*/  button_label_inactive; int /*<<< orphan*/  button_label_active; int /*<<< orphan*/  button_key_inactive; int /*<<< orphan*/  button_key_active; int /*<<< orphan*/  button_inactive; int /*<<< orphan*/  button_active; int /*<<< orphan*/  border; int /*<<< orphan*/  title; int /*<<< orphan*/  dialog; int /*<<< orphan*/  shadow; int /*<<< orphan*/  screen; } ;

/* Variables and functions */
 TYPE_1__ dlg ; 
 int /*<<< orphan*/  init_one_color (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_dialog_colors(void)
{
	init_one_color(&dlg.screen);
	init_one_color(&dlg.shadow);
	init_one_color(&dlg.dialog);
	init_one_color(&dlg.title);
	init_one_color(&dlg.border);
	init_one_color(&dlg.button_active);
	init_one_color(&dlg.button_inactive);
	init_one_color(&dlg.button_key_active);
	init_one_color(&dlg.button_key_inactive);
	init_one_color(&dlg.button_label_active);
	init_one_color(&dlg.button_label_inactive);
	init_one_color(&dlg.inputbox);
	init_one_color(&dlg.inputbox_border);
	init_one_color(&dlg.searchbox);
	init_one_color(&dlg.searchbox_title);
	init_one_color(&dlg.searchbox_border);
	init_one_color(&dlg.position_indicator);
	init_one_color(&dlg.menubox);
	init_one_color(&dlg.menubox_border);
	init_one_color(&dlg.item);
	init_one_color(&dlg.item_selected);
	init_one_color(&dlg.tag);
	init_one_color(&dlg.tag_selected);
	init_one_color(&dlg.tag_key);
	init_one_color(&dlg.tag_key_selected);
	init_one_color(&dlg.check);
	init_one_color(&dlg.check_selected);
	init_one_color(&dlg.uarrow);
	init_one_color(&dlg.darrow);
}
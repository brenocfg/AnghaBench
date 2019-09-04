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
typedef  int /*<<< orphan*/  gulong ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GtkCheckMenuItem ;

/* Variables and functions */
 int /*<<< orphan*/  g_signal_handler_block (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_signal_handler_unblock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_check_menu_item_set_active (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void singleSetChecked(GtkCheckMenuItem *menuitem, gboolean checked, gulong signal)
{
	g_signal_handler_block(menuitem, signal);
	gtk_check_menu_item_set_active(menuitem, checked);
	g_signal_handler_unblock(menuitem, signal);
}
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
typedef  int /*<<< orphan*/  GtkSpinButton ;
typedef  int /*<<< orphan*/  GtkAdjustment ;

/* Variables and functions */
 int /*<<< orphan*/  g_signal_handler_block (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_signal_handler_unblock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_adjustment_set_value (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * gtk_spin_button_get_adjustment (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void setRealSpinValue(GtkSpinButton *spinButton, int value, gulong block)
{
	GtkAdjustment *adj;

	g_signal_handler_block(spinButton, block);
	adj = gtk_spin_button_get_adjustment(spinButton);
	gtk_adjustment_set_value(adj, value);
	g_signal_handler_unblock(spinButton, block);
}
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
typedef  int /*<<< orphan*/  GtkSpinButton ;
typedef  int /*<<< orphan*/  GtkAdjustment ;

/* Variables and functions */
 scalar_t__ gtk_adjustment_get_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_spin_button_get_adjustment (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int realSpinValue(GtkSpinButton *spinButton)
{
	GtkAdjustment *adj;

	adj = gtk_spin_button_get_adjustment(spinButton);
	return (int) gtk_adjustment_get_value(adj);
}
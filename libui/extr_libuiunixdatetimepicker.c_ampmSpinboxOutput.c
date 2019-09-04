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
typedef  int /*<<< orphan*/  gpointer ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GtkSpinButton ;

/* Variables and functions */
 int /*<<< orphan*/  AM_STR ; 
 int /*<<< orphan*/  GTK_ENTRY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PM_STR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  gtk_entry_set_text (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gtk_spin_button_get_value_as_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nl_langinfo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static gboolean ampmSpinboxOutput(GtkSpinButton *sb, gpointer data)
{
	int value;

	value = gtk_spin_button_get_value_as_int(sb);
	if (value == 0)
		gtk_entry_set_text(GTK_ENTRY(sb), nl_langinfo(AM_STR));
	else
		gtk_entry_set_text(GTK_ENTRY(sb), nl_langinfo(PM_STR));
	return TRUE;
}
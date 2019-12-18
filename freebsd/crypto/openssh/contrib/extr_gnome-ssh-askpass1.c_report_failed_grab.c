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
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  GNOME_DIALOG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GNOME_MESSAGE_BOX_ERROR ; 
 int /*<<< orphan*/  GTK_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_WINDOW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_WINDOW_POPUP ; 
 int /*<<< orphan*/  GTK_WIN_POS_CENTER ; 
 int /*<<< orphan*/  gnome_dialog_run_and_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gnome_message_box_new (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_object_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_window_set_position (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
report_failed_grab (void)
{
	GtkWidget *err;

	err = gnome_message_box_new("Could not grab keyboard or mouse.\n"
		"A malicious client may be eavesdropping on your session.",
				    GNOME_MESSAGE_BOX_ERROR, "EXIT", NULL);
	gtk_window_set_position(GTK_WINDOW(err), GTK_WIN_POS_CENTER);
	gtk_object_set(GTK_OBJECT(err), "type", GTK_WINDOW_POPUP, NULL);

	gnome_dialog_run_and_close(GNOME_DIALOG(err));
}
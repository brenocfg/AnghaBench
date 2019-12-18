#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  vbox; } ;
struct TYPE_19__ {int /*<<< orphan*/  window; } ;
typedef  TYPE_1__ GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GDK_CURRENT_TIME ; 
 int /*<<< orphan*/  GDK_DISPLAY () ; 
 TYPE_7__* GNOME_DIALOG (TYPE_1__*) ; 
 int /*<<< orphan*/  GNOME_PAD ; 
 int /*<<< orphan*/  GNOME_STOCK_BUTTON_CANCEL ; 
 int /*<<< orphan*/  GNOME_STOCK_BUTTON_OK ; 
 int /*<<< orphan*/  GTK_BOX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_CONTAINER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_EDITABLE (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_ENTRY (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_OBJECT (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_WINDOW (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_WINDOW_POPUP ; 
 int /*<<< orphan*/  GTK_WIN_POS_CENTER ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XGrabServer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XUngrabServer (int /*<<< orphan*/ ) ; 
 char** g_strsplit (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdk_flush () ; 
 scalar_t__ gdk_keyboard_grab (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdk_keyboard_ungrab (int /*<<< orphan*/ ) ; 
 scalar_t__ gdk_pointer_grab (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdk_pointer_ungrab (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * getenv (char*) ; 
 int /*<<< orphan*/  gnome_dialog_close (TYPE_7__*) ; 
 int /*<<< orphan*/  gnome_dialog_close_hides (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnome_dialog_editable_enters (TYPE_7__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* gnome_dialog_new (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int gnome_dialog_run (TYPE_7__*) ; 
 int /*<<< orphan*/  gnome_dialog_set_default (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_box_pack_start (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_container_set_border_width (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* gtk_entry_get_text (int /*<<< orphan*/ ) ; 
 TYPE_1__* gtk_entry_new () ; 
 int /*<<< orphan*/  gtk_entry_set_text (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gtk_entry_set_visibility (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* gtk_label_new (char*) ; 
 int /*<<< orphan*/  gtk_object_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_grab_focus (TYPE_1__*) ; 
 int /*<<< orphan*/  gtk_widget_show_all (TYPE_1__*) ; 
 int /*<<< orphan*/  gtk_window_set_policy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_window_set_position (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  report_failed_grab () ; 
 int /*<<< orphan*/  strlen (char*) ; 

int
passphrase_dialog(char *message)
{
	char *passphrase;
	char **messages;
	int result, i, grab_server, grab_pointer;
	GtkWidget *dialog, *entry, *label;

	grab_server = (getenv("GNOME_SSH_ASKPASS_GRAB_SERVER") != NULL);
	grab_pointer = (getenv("GNOME_SSH_ASKPASS_GRAB_POINTER") != NULL);

	dialog = gnome_dialog_new("OpenSSH", GNOME_STOCK_BUTTON_OK,
	    GNOME_STOCK_BUTTON_CANCEL, NULL);

	messages = g_strsplit(message, "\\n", 0);
	if (messages)
		for(i = 0; messages[i]; i++) {
			label = gtk_label_new(messages[i]);
			gtk_box_pack_start(GTK_BOX(GNOME_DIALOG(dialog)->vbox),
			    label, FALSE, FALSE, 0);
		}

	entry = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(GNOME_DIALOG(dialog)->vbox), entry, FALSE,
	    FALSE, 0);
	gtk_entry_set_visibility(GTK_ENTRY(entry), FALSE);
	gtk_widget_grab_focus(entry);

	/* Center window and prepare for grab */
	gtk_object_set(GTK_OBJECT(dialog), "type", GTK_WINDOW_POPUP, NULL);
	gnome_dialog_set_default(GNOME_DIALOG(dialog), 0);
	gtk_window_set_position (GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
	gtk_window_set_policy(GTK_WINDOW(dialog), FALSE, FALSE, TRUE);
	gnome_dialog_close_hides(GNOME_DIALOG(dialog), TRUE);
	gtk_container_set_border_width(GTK_CONTAINER(GNOME_DIALOG(dialog)->vbox),
	    GNOME_PAD);
	gtk_widget_show_all(dialog);

	/* Grab focus */
	if (grab_server)
		XGrabServer(GDK_DISPLAY());
	if (grab_pointer && gdk_pointer_grab(dialog->window, TRUE, 0,
	    NULL, NULL, GDK_CURRENT_TIME))
		goto nograb;
	if (gdk_keyboard_grab(dialog->window, FALSE, GDK_CURRENT_TIME))
		goto nograbkb;

	/* Make <enter> close dialog */
	gnome_dialog_editable_enters(GNOME_DIALOG(dialog), GTK_EDITABLE(entry));

	/* Run dialog */
	result = gnome_dialog_run(GNOME_DIALOG(dialog));

	/* Ungrab */
	if (grab_server)
		XUngrabServer(GDK_DISPLAY());
	if (grab_pointer)
		gdk_pointer_ungrab(GDK_CURRENT_TIME);
	gdk_keyboard_ungrab(GDK_CURRENT_TIME);
	gdk_flush();

	/* Report passphrase if user selected OK */
	passphrase = gtk_entry_get_text(GTK_ENTRY(entry));
	if (result == 0)
		puts(passphrase);
		
	/* Zero passphrase in memory */
	memset(passphrase, '\0', strlen(passphrase));
	gtk_entry_set_text(GTK_ENTRY(entry), passphrase);
			
	gnome_dialog_close(GNOME_DIALOG(dialog));
	return (result == 0 ? 0 : -1);

	/* At least one grab failed - ungrab what we got, and report
	   the failure to the user.  Note that XGrabServer() cannot
	   fail.  */
 nograbkb:
	gdk_pointer_ungrab(GDK_CURRENT_TIME);
 nograb:
	if (grab_server)
		XUngrabServer(GDK_DISPLAY());
	gnome_dialog_close(GNOME_DIALOG(dialog));
	
	report_failed_grab();
	return (-1);
}
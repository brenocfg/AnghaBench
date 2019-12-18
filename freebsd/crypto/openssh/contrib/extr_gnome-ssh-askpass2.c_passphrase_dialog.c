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
typedef  scalar_t__ GdkGrabStatus ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GDK_CURRENT_TIME ; 
 scalar_t__ GDK_GRAB_SUCCESS ; 
 int GRAB_TRIES ; 
 int GRAB_WAIT ; 
 int /*<<< orphan*/  GTK_BOX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_BUTTONS_OK_CANCEL ; 
 int /*<<< orphan*/  GTK_DIALOG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_ENTRY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_MESSAGE_QUESTION ; 
 int GTK_RESPONSE_OK ; 
 int /*<<< orphan*/  GTK_WIDGET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_WINDOW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_WINDOW_TOPLEVEL ; 
 int /*<<< orphan*/  GTK_WIN_POS_CENTER ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XUngrabServer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_locale_from_utf8 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* g_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdk_flush () ; 
 scalar_t__ gdk_keyboard_grab (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdk_keyboard_ungrab (int /*<<< orphan*/ ) ; 
 scalar_t__ gdk_pointer_grab (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdk_pointer_ungrab (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdk_x11_get_default_xdisplay () ; 
 int /*<<< orphan*/  gdk_x11_grab_server () ; 
 int /*<<< orphan*/ * getenv (char*) ; 
 int /*<<< orphan*/  gtk_box_pack_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_dialog_get_content_area (int /*<<< orphan*/ ) ; 
 int gtk_dialog_run (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_dialog_set_default_response (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_entry_get_text (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_entry_new () ; 
 int /*<<< orphan*/  gtk_entry_set_text (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gtk_entry_set_visibility (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_message_dialog_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  gtk_widget_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_get_window (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_grab_focus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_show_now (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_window_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_window_set_keep_above (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_window_set_position (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_window_set_title (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (char*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_dialog ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  report_failed_grab (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static int
passphrase_dialog(char *message)
{
	const char *failed;
	char *passphrase, *local;
	int result, grab_tries, grab_server, grab_pointer;
	GtkWidget *parent_window, *dialog, *entry;
	GdkGrabStatus status;

	grab_server = (getenv("GNOME_SSH_ASKPASS_GRAB_SERVER") != NULL);
	grab_pointer = (getenv("GNOME_SSH_ASKPASS_GRAB_POINTER") != NULL);
	grab_tries = 0;

	/* Create an invisible parent window so that GtkDialog doesn't
	 * complain.  */
	parent_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	dialog = gtk_message_dialog_new(GTK_WINDOW(parent_window), 0,
					GTK_MESSAGE_QUESTION,
					GTK_BUTTONS_OK_CANCEL,
					"%s",
					message);

	entry = gtk_entry_new();
	gtk_box_pack_start(
	    GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(dialog))), entry,
	    FALSE, FALSE, 0);
	gtk_entry_set_visibility(GTK_ENTRY(entry), FALSE);
	gtk_widget_grab_focus(entry);
	gtk_widget_show(entry);

	gtk_window_set_title(GTK_WINDOW(dialog), "OpenSSH");
	gtk_window_set_position (GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
	gtk_window_set_keep_above(GTK_WINDOW(dialog), TRUE);

	/* Make <enter> close dialog */
	gtk_dialog_set_default_response(GTK_DIALOG(dialog), GTK_RESPONSE_OK);
	g_signal_connect(G_OBJECT(entry), "activate",
			 G_CALLBACK(ok_dialog), dialog);

	gtk_window_set_keep_above(GTK_WINDOW(dialog), TRUE);

	/* Grab focus */
	gtk_widget_show_now(dialog);
	if (grab_pointer) {
		for(;;) {
			status = gdk_pointer_grab(
			    (gtk_widget_get_window(GTK_WIDGET(dialog))), TRUE,
			    0, NULL, NULL, GDK_CURRENT_TIME);
			if (status == GDK_GRAB_SUCCESS)
				break;
			usleep(GRAB_WAIT * 1000);
			if (++grab_tries > GRAB_TRIES) {
				failed = "mouse";
				goto nograb;
			}
		}
	}
	for(;;) {
		status = gdk_keyboard_grab(
		    gtk_widget_get_window(GTK_WIDGET(dialog)), FALSE,
		    GDK_CURRENT_TIME);
		if (status == GDK_GRAB_SUCCESS)
			break;
		usleep(GRAB_WAIT * 1000);
		if (++grab_tries > GRAB_TRIES) {
			failed = "keyboard";
			goto nograbkb;
		}
	}
	if (grab_server) {
		gdk_x11_grab_server();
	}

	result = gtk_dialog_run(GTK_DIALOG(dialog));

	/* Ungrab */
	if (grab_server)
		XUngrabServer(gdk_x11_get_default_xdisplay());
	if (grab_pointer)
		gdk_pointer_ungrab(GDK_CURRENT_TIME);
	gdk_keyboard_ungrab(GDK_CURRENT_TIME);
	gdk_flush();

	/* Report passphrase if user selected OK */
	passphrase = g_strdup(gtk_entry_get_text(GTK_ENTRY(entry)));
	if (result == GTK_RESPONSE_OK) {
		local = g_locale_from_utf8(passphrase, strlen(passphrase),
					   NULL, NULL, NULL);
		if (local != NULL) {
			puts(local);
			memset(local, '\0', strlen(local));
			g_free(local);
		} else {
			puts(passphrase);
		}
	}
		
	/* Zero passphrase in memory */
	memset(passphrase, '\b', strlen(passphrase));
	gtk_entry_set_text(GTK_ENTRY(entry), passphrase);
	memset(passphrase, '\0', strlen(passphrase));
	g_free(passphrase);
			
	gtk_widget_destroy(dialog);
	return (result == GTK_RESPONSE_OK ? 0 : -1);

	/* At least one grab failed - ungrab what we got, and report
	   the failure to the user.  Note that XGrabServer() cannot
	   fail.  */
 nograbkb:
	gdk_pointer_ungrab(GDK_CURRENT_TIME);
 nograb:
	if (grab_server)
		XUngrabServer(gdk_x11_get_default_xdisplay());
	gtk_widget_destroy(dialog);
	
	report_failed_grab(parent_window, failed);

	return (-1);
}
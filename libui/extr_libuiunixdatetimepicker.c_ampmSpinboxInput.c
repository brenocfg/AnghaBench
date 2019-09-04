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
typedef  scalar_t__ gpointer ;
typedef  int /*<<< orphan*/  gint ;
typedef  char gchar ;
typedef  int /*<<< orphan*/  GtkSpinButton ;

/* Variables and functions */
 int /*<<< orphan*/  AM_STR ; 
 int /*<<< orphan*/  GTK_ENTRY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_INPUT_ERROR ; 
 int /*<<< orphan*/  PM_STR ; 
 int /*<<< orphan*/  TRUE ; 
 char g_ascii_tolower (char const) ; 
 char* gtk_entry_get_text (int /*<<< orphan*/ ) ; 
 char const* nl_langinfo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static gint ampmSpinboxInput(GtkSpinButton *sb, gpointer ptr, gpointer data)
{
	double *out = (double *) ptr;
	const gchar *text;
	char firstAM, firstPM;

	text = gtk_entry_get_text(GTK_ENTRY(sb));
	// LONGTERM don't use ASCII here for case insensitivity
	firstAM = g_ascii_tolower(nl_langinfo(AM_STR)[0]);
	firstPM = g_ascii_tolower(nl_langinfo(PM_STR)[0]);
	for (; *text != '\0'; text++)
		if (g_ascii_tolower(*text) == firstAM) {
			*out = 0;
			return TRUE;
		} else if (g_ascii_tolower(*text) == firstPM) {
			*out = 1;
			return TRUE;
		}
	return GTK_INPUT_ERROR;
}
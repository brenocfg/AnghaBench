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
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GtkSpinButton ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_ENTRY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_strdup_printf (char*,int) ; 
 int /*<<< orphan*/  gtk_entry_set_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int realSpinValue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static gboolean hoursSpinboxOutput(GtkSpinButton *sb, gpointer data)
{
	gchar *text;
	int value;

	value = realSpinValue(sb);
	if (value == 0)		// 0 internally is 12 to the user
		value = 12;
	text = g_strdup_printf("%d", value);
	gtk_entry_set_text(GTK_ENTRY(sb), text);
	g_free(text);
	return TRUE;
}
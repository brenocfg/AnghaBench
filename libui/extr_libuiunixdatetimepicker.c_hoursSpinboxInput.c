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
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GtkSpinButton ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_ENTRY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_INPUT_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ g_strtod (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_entry_get_text (int /*<<< orphan*/ ) ; 

__attribute__((used)) static gint hoursSpinboxInput(GtkSpinButton *sb, gpointer ptr, gpointer data)
{
	double *out = (double *) ptr;
	const gchar *text;
	int value;

	text = gtk_entry_get_text(GTK_ENTRY(sb));
	value = (int) g_strtod(text, NULL);
	if (value < 0 || value > 12)
		return GTK_INPUT_ERROR;
	if (value == 12)		// 12 to the user is 0 internally
		value = 0;
	*out = (double) value;
	return TRUE;
}
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
typedef  int /*<<< orphan*/  uiEntry ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_ENTRY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * finishNewEntry (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * gtk_entry_new () ; 
 int /*<<< orphan*/  gtk_entry_set_visibility (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uiEntry *uiNewPasswordEntry(void)
{
	GtkWidget *e;

	e = gtk_entry_new();
	gtk_entry_set_visibility(GTK_ENTRY(e), FALSE);
	return finishNewEntry(e, "changed");
}
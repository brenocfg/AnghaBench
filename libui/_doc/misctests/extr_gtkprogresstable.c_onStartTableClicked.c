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
typedef  int /*<<< orphan*/  GtkButton ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_timeout_add (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_set_sensitive (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pbarStarted ; 
 scalar_t__ pbarValue ; 
 int /*<<< orphan*/  pulseTable ; 
 int /*<<< orphan*/  startTable ; 

__attribute__((used)) static void onStartTableClicked(GtkButton *button, gpointer data)
{
	pbarStarted = TRUE;
	pbarValue = 0;

	gtk_widget_set_sensitive(startTable, FALSE);
	g_timeout_add(100, pulseTable, NULL);
}
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
typedef  scalar_t__ guint ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_CONTAINER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freeMenu ; 
 int /*<<< orphan*/  gtk_container_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

void uiprivFreeMenubar(GtkWidget *mb)
{
	guint i;

	i = 0;
	gtk_container_foreach(GTK_CONTAINER(mb), freeMenu, &i);
	// no need to worry about destroying any widgets; destruction of the window they're in will do it for us
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int disabled; int /*<<< orphan*/  windows; } ;
typedef  TYPE_1__ uiMenuItem ;
typedef  int /*<<< orphan*/  gpointer ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GHashTableIter ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_WIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_hash_table_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ g_hash_table_iter_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_set_sensitive (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void menuItemEnableDisable(uiMenuItem *item, gboolean enabled)
{
	GHashTableIter iter;
	gpointer widget;

	item->disabled = !enabled;
	g_hash_table_iter_init(&iter, item->windows);
	while (g_hash_table_iter_next(&iter, &widget, NULL))
		gtk_widget_set_sensitive(GTK_WIDGET(widget), enabled);
}
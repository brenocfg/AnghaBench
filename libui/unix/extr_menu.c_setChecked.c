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
struct TYPE_3__ {int /*<<< orphan*/  checked; int /*<<< orphan*/  windows; } ;
typedef  TYPE_1__ uiMenuItem ;
struct menuItemWindow {int /*<<< orphan*/  signal; } ;
typedef  scalar_t__ gpointer ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GHashTableIter ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_CHECK_MENU_ITEM (scalar_t__) ; 
 int /*<<< orphan*/  g_hash_table_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ g_hash_table_iter_next (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  singleSetChecked (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setChecked(uiMenuItem *item, gboolean checked)
{
	GHashTableIter iter;
	gpointer widget;
	gpointer ww;
	struct menuItemWindow *w;

	item->checked = checked;
	g_hash_table_iter_init(&iter, item->windows);
	while (g_hash_table_iter_next(&iter, &widget, &ww)) {
		w = (struct menuItemWindow *) ww;
		singleSetChecked(GTK_CHECK_MENU_ITEM(widget), item->checked, w->signal);
	}
}
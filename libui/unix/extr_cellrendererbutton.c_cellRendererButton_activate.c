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
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkCellRendererState ;
typedef  int /*<<< orphan*/  GtkCellRenderer ;
typedef  int /*<<< orphan*/  GdkRectangle ;
typedef  int /*<<< orphan*/  GdkEvent ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  clickedSignal ; 
 int /*<<< orphan*/  g_signal_emit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static gboolean cellRendererButton_activate(GtkCellRenderer *r, GdkEvent *e, GtkWidget *widget, const gchar *path, const GdkRectangle *background_area, const GdkRectangle *cell_area, GtkCellRendererState flags)
{
	g_signal_emit(r, clickedSignal, 0, path);
	return TRUE;
}
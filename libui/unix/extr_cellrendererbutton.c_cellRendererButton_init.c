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
typedef  int /*<<< orphan*/  cellRendererButton ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_CELL_RENDERER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_CELL_RENDERER_MODE_ACTIVATABLE ; 
 int /*<<< orphan*/  g_object_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_cell_renderer_set_padding (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void cellRendererButton_init(cellRendererButton *c)
{
	g_object_set(c, "mode", GTK_CELL_RENDERER_MODE_ACTIVATABLE, NULL);
	// the standard cell renderers all do this
	gtk_cell_renderer_set_padding(GTK_CELL_RENDERER(c), 2, 2);
}
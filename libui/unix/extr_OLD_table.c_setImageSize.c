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
typedef  int gint ;
typedef  int /*<<< orphan*/  GtkCellRenderer ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GTK_ICON_SIZE_MENU ; 
 int MAX (int,int) ; 
 int /*<<< orphan*/  gtk_cell_renderer_get_padding (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  gtk_cell_renderer_set_fixed_size (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ gtk_icon_size_lookup (int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static void setImageSize(GtkCellRenderer *r)
{
	gint size;
	gint width, height;
	gint xpad, ypad;

	size = 16;		// fallback used by GtkFileChooserWidget
	if (gtk_icon_size_lookup(GTK_ICON_SIZE_MENU, &width, &height) != FALSE)
		size = MAX(width, height);
	gtk_cell_renderer_get_padding(r, &xpad, &ypad);
	gtk_cell_renderer_set_fixed_size(r,
		2 * xpad + size,
		2 * ypad + size);
}
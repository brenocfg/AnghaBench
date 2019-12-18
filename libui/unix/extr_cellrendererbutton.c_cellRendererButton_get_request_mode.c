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
typedef  int /*<<< orphan*/  GtkSizeRequestMode ;
typedef  int /*<<< orphan*/  GtkCellRenderer ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_SIZE_REQUEST_HEIGHT_FOR_WIDTH ; 

__attribute__((used)) static GtkSizeRequestMode cellRendererButton_get_request_mode(GtkCellRenderer *r)
{
	return GTK_SIZE_REQUEST_HEIGHT_FOR_WIDTH;
}
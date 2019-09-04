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
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/ * GTK_WIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_object_new (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setLabel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setTimeOnly (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiprivDateTimePickerWidget (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiprivDateTimePickerWidgetType ; 

__attribute__((used)) static GtkWidget *newTP(void)
{
	GtkWidget *w;

	w = GTK_WIDGET(g_object_new(uiprivDateTimePickerWidgetType, "label", "", NULL));
	setTimeOnly(uiprivDateTimePickerWidget(w));
	setLabel(uiprivDateTimePickerWidget(w));
	return w;
}
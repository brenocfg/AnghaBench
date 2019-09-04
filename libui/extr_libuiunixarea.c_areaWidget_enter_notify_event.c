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
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GdkEventCrossing ;

/* Variables and functions */
 int /*<<< orphan*/  areaWidget (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  onCrossing (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static gboolean areaWidget_enter_notify_event(GtkWidget *w, GdkEventCrossing *e)
{
	return onCrossing(areaWidget(w), 0);
}
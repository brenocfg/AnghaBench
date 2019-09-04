#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uiprivDateTimePickerWidgetClass ;
struct TYPE_2__ {int /*<<< orphan*/  finalize; int /*<<< orphan*/  dispose; } ;

/* Variables and functions */
 TYPE_1__* G_OBJECT_CLASS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  G_SIGNAL_RUN_LAST ; 
 int /*<<< orphan*/  G_TYPE_FROM_CLASS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  G_TYPE_NONE ; 
 int /*<<< orphan*/  changedSignal ; 
 int /*<<< orphan*/  g_signal_new (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiprivDateTimePickerWidget_dispose ; 
 int /*<<< orphan*/  uiprivDateTimePickerWidget_finalize ; 

__attribute__((used)) static void uiprivDateTimePickerWidget_class_init(uiprivDateTimePickerWidgetClass *class)
{
	G_OBJECT_CLASS(class)->dispose = uiprivDateTimePickerWidget_dispose;
	G_OBJECT_CLASS(class)->finalize = uiprivDateTimePickerWidget_finalize;

	changedSignal = g_signal_new("changed",
		G_TYPE_FROM_CLASS(class),
		G_SIGNAL_RUN_LAST,
		0,
		NULL, NULL, NULL,
		G_TYPE_NONE,
		0);
}
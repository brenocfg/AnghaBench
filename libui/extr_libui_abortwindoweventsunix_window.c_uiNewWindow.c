#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uiWindow ;
struct TYPE_4__ {int /*<<< orphan*/  widget; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  defaultOnPositionContentSizeChanged ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  onConfigure ; 
 int /*<<< orphan*/  uiWindowOnPositionChanged (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* w ; 

uiWindow *uiNewWindow(const char *title, int width, int height, int hasMenubar)
{
//	g_signal_connect(w->widget, "delete-event", G_CALLBACK(onClosing), w);
	g_signal_connect(w->widget, "configure-event", G_CALLBACK(onConfigure), w);
//	g_signal_connect(w->childHolderWidget, "size-allocate", G_CALLBACK(onSizeAllocate), w);
//	uiWindowOnClosing(w, defaultOnClosing, NULL);
	uiWindowOnPositionChanged(w, defaultOnPositionContentSizeChanged, NULL);
//	uiWindowOnContentSizeChanged(w, defaultOnPositionContentSizeChanged, NULL);
}
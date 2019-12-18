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
struct TYPE_3__ {int /*<<< orphan*/  areaWidget; } ;
typedef  TYPE_1__ uiArea ;

/* Variables and functions */
 int /*<<< orphan*/  gtk_widget_queue_draw (int /*<<< orphan*/ ) ; 

void uiAreaQueueRedrawAll(uiArea *a)
{
	gtk_widget_queue_draw(a->areaWidget);
}
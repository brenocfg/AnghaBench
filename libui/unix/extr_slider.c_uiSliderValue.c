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
struct TYPE_3__ {int /*<<< orphan*/  range; } ;
typedef  TYPE_1__ uiSlider ;

/* Variables and functions */
 int gtk_range_get_value (int /*<<< orphan*/ ) ; 

int uiSliderValue(uiSlider *s)
{
	return gtk_range_get_value(s->range);
}
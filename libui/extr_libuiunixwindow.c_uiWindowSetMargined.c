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
struct TYPE_3__ {int margined; int /*<<< orphan*/  childHolderContainer; } ;
typedef  TYPE_1__ uiWindow ;

/* Variables and functions */
 int /*<<< orphan*/  uiprivSetMargined (int /*<<< orphan*/ ,int) ; 

void uiWindowSetMargined(uiWindow *w, int margined)
{
	w->margined = margined;
	uiprivSetMargined(w->childHolderContainer, w->margined);
}
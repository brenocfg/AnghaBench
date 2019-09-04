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
struct TYPE_3__ {int padded; int /*<<< orphan*/  box; scalar_t__ vertical; } ;
typedef  TYPE_1__ uiBox ;

/* Variables and functions */
 int /*<<< orphan*/  gtk_box_set_spacing (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiprivGTKXPadding ; 
 int /*<<< orphan*/  uiprivGTKYPadding ; 

void uiBoxSetPadded(uiBox *b, int padded)
{
	b->padded = padded;
	if (b->padded)
		if (b->vertical)
			gtk_box_set_spacing(b->box, uiprivGTKYPadding);
		else
			gtk_box_set_spacing(b->box, uiprivGTKXPadding);
	else
		gtk_box_set_spacing(b->box, 0);
}
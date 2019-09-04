#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  cc; } ;
typedef  TYPE_1__ uiColorButton ;
struct TYPE_6__ {double red; double green; double blue; double alpha; } ;
typedef  TYPE_2__ GdkRGBA ;

/* Variables and functions */
 int /*<<< orphan*/  gtk_color_chooser_get_rgba (int /*<<< orphan*/ ,TYPE_2__*) ; 

void uiColorButtonColor(uiColorButton *b, double *r, double *g, double *bl, double *a)
{
	GdkRGBA rgba;

	gtk_color_chooser_get_rgba(b->cc, &rgba);
	*r = rgba.red;
	*g = rgba.green;
	*bl = rgba.blue;
	*a = rgba.alpha;
}
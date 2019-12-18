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
struct TYPE_3__ {double red; double green; double blue; double alpha; } ;
typedef  TYPE_1__ GdkRGBA ;

/* Variables and functions */
 void* gdk_rgba_copy (TYPE_1__*) ; 

void *uiTableModelGiveColor(double r, double g, double b, double a)
{
	GdkRGBA rgba;

	rgba.red = r;
	rgba.green = g;
	rgba.blue = b;
	rgba.alpha = a;
	return gdk_rgba_copy(&rgba);
}
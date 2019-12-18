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
struct videomode {int hdisplay; int vdisplay; int /*<<< orphan*/  vtotal; int /*<<< orphan*/  htotal; int /*<<< orphan*/  dot_clock; } ;

/* Variables and functions */
 int DOT_CLOCK_TO_HZ (int /*<<< orphan*/ ) ; 
 int FB_DIVIDE (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
jzlcd_get_bandwidth(const struct videomode *mode)
{
	int refresh;

	refresh = FB_DIVIDE(FB_DIVIDE(DOT_CLOCK_TO_HZ(mode->dot_clock),
	    mode->htotal), mode->vtotal);

	return mode->hdisplay * mode->vdisplay * refresh;
}
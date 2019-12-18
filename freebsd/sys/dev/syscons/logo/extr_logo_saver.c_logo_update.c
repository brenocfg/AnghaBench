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
typedef  int /*<<< orphan*/  video_adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  logo_blit (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ logo_h ; 
 scalar_t__ logo_w ; 
 scalar_t__ scrh ; 
 scalar_t__ scrw ; 

__attribute__((used)) static void
logo_update(video_adapter_t *adp)
{
	static int xpos = 0, ypos = 0;
	static int xinc = 1, yinc = 1;
	
	/* Turn when you hit the edge */
	if ((xpos + logo_w + xinc > scrw) || (xpos + xinc < 0))
		xinc = -xinc;
	if ((ypos + logo_h + yinc > scrh) || (ypos + yinc < 0))
		yinc = -yinc;
	xpos += xinc;
	ypos += yinc;
	
	/* XXX Relies on margin around logo to erase trail */
	logo_blit(adp, xpos, ypos);
}
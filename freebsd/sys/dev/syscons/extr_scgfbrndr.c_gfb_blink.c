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
struct TYPE_4__ {int status; } ;
typedef  TYPE_1__ scr_stat ;

/* Variables and functions */
 int VR_CURSOR_BLINK ; 
 int VR_CURSOR_ON ; 
 int /*<<< orphan*/  gfb_cursor (TYPE_1__*,int,int,int,int) ; 
 int pxlblinkrate ; 

__attribute__((used)) static void
gfb_blink(scr_stat *scp, int at, int flip)
{
	if (!(scp->status & VR_CURSOR_BLINK))
		return;
	if (!(++pxlblinkrate & 4))
		return;
	pxlblinkrate = 0;
	scp->status ^= VR_CURSOR_ON;
	gfb_cursor(scp, at, scp->status & VR_CURSOR_BLINK,
	    scp->status & VR_CURSOR_ON, flip);
}
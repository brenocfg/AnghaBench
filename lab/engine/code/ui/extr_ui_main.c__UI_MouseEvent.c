#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int bias; int xscale; int cursorx; scalar_t__ cursory; } ;
struct TYPE_4__ {TYPE_1__ uiDC; } ;

/* Variables and functions */
 int /*<<< orphan*/  Display_MouseMove (int /*<<< orphan*/ *,int,scalar_t__) ; 
 scalar_t__ Menu_Count () ; 
 scalar_t__ SCREEN_HEIGHT ; 
 int SCREEN_WIDTH ; 
 TYPE_2__ uiInfo ; 

void _UI_MouseEvent( int dx, int dy )
{
	int bias;

	// convert X bias to 640 coords
	bias = uiInfo.uiDC.bias / uiInfo.uiDC.xscale;

	// update mouse screen position
	uiInfo.uiDC.cursorx += dx;
	if (uiInfo.uiDC.cursorx < -bias)
		uiInfo.uiDC.cursorx = -bias;
	else if (uiInfo.uiDC.cursorx > SCREEN_WIDTH+bias)
		uiInfo.uiDC.cursorx = SCREEN_WIDTH+bias;

	uiInfo.uiDC.cursory += dy;
	if (uiInfo.uiDC.cursory < 0)
		uiInfo.uiDC.cursory = 0;
	else if (uiInfo.uiDC.cursory > SCREEN_HEIGHT)
		uiInfo.uiDC.cursory = SCREEN_HEIGHT;

  if (Menu_Count() > 0) {
    //menuDef_t *menu = Menu_GetFocused();
    //Menu_HandleMouseMove(menu, uiInfo.uiDC.cursorx, uiInfo.uiDC.cursory);
		Display_MouseMove(NULL, uiInfo.uiDC.cursorx, uiInfo.uiDC.cursory);
  }

}
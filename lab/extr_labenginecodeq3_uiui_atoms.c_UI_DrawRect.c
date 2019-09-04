#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  whiteShader; } ;

/* Variables and functions */
 int /*<<< orphan*/  UI_AdjustFrom640 (float*,float*,float*,float*) ; 
 int /*<<< orphan*/  trap_R_DrawStretchPic (float,float,int,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_R_SetColor (float const*) ; 
 TYPE_1__ uis ; 

void UI_DrawRect( float x, float y, float width, float height, const float *color ) {
	trap_R_SetColor( color );

	UI_AdjustFrom640( &x, &y, &width, &height );

	trap_R_DrawStretchPic( x, y, width, 1, 0, 0, 0, 0, uis.whiteShader );
	trap_R_DrawStretchPic( x, y, 1, height, 0, 0, 0, 0, uis.whiteShader );
	trap_R_DrawStretchPic( x, y + height - 1, width, 1, 0, 0, 0, 0, uis.whiteShader );
	trap_R_DrawStretchPic( x + width - 1, y, 1, height, 0, 0, 0, 0, uis.whiteShader );

	trap_R_SetColor( NULL );
}
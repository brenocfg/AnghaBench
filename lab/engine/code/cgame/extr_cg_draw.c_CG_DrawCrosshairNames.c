#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t crosshairClientNum; int /*<<< orphan*/  crosshairClientTime; scalar_t__ renderingThirdPerson; } ;
struct TYPE_9__ {int /*<<< orphan*/  integer; } ;
struct TYPE_8__ {int /*<<< orphan*/  integer; } ;
struct TYPE_7__ {TYPE_1__* clientinfo; } ;
struct TYPE_6__ {char* name; } ;

/* Variables and functions */
 float BIGCHAR_WIDTH ; 
 int /*<<< orphan*/  CG_DrawBigString (int,int,char*,float) ; 
 float CG_DrawStrlen (char*) ; 
 float* CG_FadeColor (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CG_ScanForCrosshairEntity () ; 
 int /*<<< orphan*/  CG_Text_Paint (int,int,float,float*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float CG_Text_Width (char*,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITEM_TEXTSTYLE_SHADOWED ; 
 TYPE_5__ cg ; 
 TYPE_4__ cg_drawCrosshair ; 
 TYPE_3__ cg_drawCrosshairNames ; 
 TYPE_2__ cgs ; 
 int /*<<< orphan*/  trap_R_SetColor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void CG_DrawCrosshairNames( void ) {
	float		*color;
	char		*name;
	float		w;

	if ( !cg_drawCrosshair.integer ) {
		return;
	}
	if ( !cg_drawCrosshairNames.integer ) {
		return;
	}
	if ( cg.renderingThirdPerson ) {
		return;
	}

	// scan the known entities to see if the crosshair is sighted on one
	CG_ScanForCrosshairEntity();

	// draw the name of the player being looked at
	color = CG_FadeColor( cg.crosshairClientTime, 1000 );
	if ( !color ) {
		trap_R_SetColor( NULL );
		return;
	}

	name = cgs.clientinfo[ cg.crosshairClientNum ].name;
#ifdef MISSIONPACK
	color[3] *= 0.5f;
	w = CG_Text_Width(name, 0.3f, 0);
	CG_Text_Paint( 320 - w / 2, 190, 0.3f, color, name, 0, 0, ITEM_TEXTSTYLE_SHADOWED);
#else
	w = CG_DrawStrlen( name ) * BIGCHAR_WIDTH;
	CG_DrawBigString( 320 - w / 2, 170, name, color[3] * 0.5f );
#endif
	trap_R_SetColor( NULL );
}
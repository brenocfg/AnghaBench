#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ serverTime; } ;
typedef  TYPE_3__ usercmd_t ;
struct TYPE_9__ {scalar_t__ time; TYPE_2__* snap; } ;
struct TYPE_6__ {scalar_t__ commandTime; } ;
struct TYPE_7__ {TYPE_1__ ps; } ;

/* Variables and functions */
 int BIGCHAR_WIDTH ; 
 int /*<<< orphan*/  CG_DrawBigString (int,int,char const*,float) ; 
 int /*<<< orphan*/  CG_DrawPic (float,float,int,int,int /*<<< orphan*/ ) ; 
 int CG_DrawStrlen (char const*) ; 
 int CMD_BACKUP ; 
 TYPE_5__ cg ; 
 int trap_GetCurrentCmdNumber () ; 
 int /*<<< orphan*/  trap_GetUserCmd (int,TYPE_3__*) ; 
 int /*<<< orphan*/  trap_R_RegisterShader (char*) ; 

__attribute__((used)) static void CG_DrawDisconnect( void ) {
	float		x, y;
	int			cmdNum;
	usercmd_t	cmd;
	const char		*s;
	int			w;

	// draw the phone jack if we are completely past our buffers
	cmdNum = trap_GetCurrentCmdNumber() - CMD_BACKUP + 1;
	trap_GetUserCmd( cmdNum, &cmd );
	if ( cmd.serverTime <= cg.snap->ps.commandTime
		|| cmd.serverTime > cg.time ) {	// special check for map_restart
		return;
	}

	// also add text in center of screen
	s = "Connection Interrupted";
	w = CG_DrawStrlen( s ) * BIGCHAR_WIDTH;
	CG_DrawBigString( 320 - w/2, 100, s, 1.0F);

	// blink the icon
	if ( ( cg.time >> 9 ) & 1 ) {
		return;
	}

#ifdef MISSIONPACK
	x = 640 - 48;
	y = 480 - 144;
#else
	x = 640 - 48;
	y = 480 - 48;
#endif

	CG_DrawPic( x, y, 48, 48, trap_R_RegisterShader("gfx/2d/net.tga" ) );
}
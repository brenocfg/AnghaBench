#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  double* vec4_t ;
struct TYPE_24__ {double value; } ;
struct TYPE_23__ {double value; } ;
struct TYPE_22__ {double value; } ;
struct TYPE_21__ {double value; } ;
struct TYPE_20__ {int integer; } ;
struct TYPE_19__ {scalar_t__ integer; } ;
struct TYPE_17__ {int /*<<< orphan*/  teamStatusBar; } ;
struct TYPE_18__ {int teamLastChatPos; int teamChatPos; scalar_t__* teamChatMsgTimes; int /*<<< orphan*/ * teamChatMsgs; TYPE_2__ media; TYPE_1__* clientinfo; } ;
struct TYPE_16__ {scalar_t__ team; } ;
struct TYPE_15__ {scalar_t__ time; size_t clientNum; } ;
struct TYPE_14__ {double value; } ;
struct TYPE_13__ {double value; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_DrawPic (scalar_t__,scalar_t__,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_DrawStringExt (scalar_t__,scalar_t__,int /*<<< orphan*/ ,double*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ CHATLOC_X ; 
 scalar_t__ CHATLOC_Y ; 
 int TEAMCHAT_HEIGHT ; 
 scalar_t__ TEAM_BLUE ; 
 scalar_t__ TEAM_RED ; 
 int TINYCHAR_HEIGHT ; 
 scalar_t__ TINYCHAR_WIDTH ; 
 TYPE_12__ cg ; 
 TYPE_11__ cg_blueteam_b ; 
 TYPE_10__ cg_blueteam_g ; 
 TYPE_9__ cg_blueteam_r ; 
 TYPE_8__ cg_redteam_b ; 
 TYPE_7__ cg_redteam_g ; 
 TYPE_6__ cg_redteam_r ; 
 TYPE_5__ cg_teamChatHeight ; 
 TYPE_4__ cg_teamChatTime ; 
 TYPE_3__ cgs ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  trap_R_SetColor (double*) ; 

__attribute__((used)) static void CG_DrawTeamInfo( void ) {
	int h;
	int i;
	vec4_t		hcolor;
	int		chatHeight;

#define CHATLOC_Y 420 // bottom end
#define CHATLOC_X 0

	if (cg_teamChatHeight.integer < TEAMCHAT_HEIGHT)
		chatHeight = cg_teamChatHeight.integer;
	else
		chatHeight = TEAMCHAT_HEIGHT;
	if (chatHeight <= 0)
		return; // disabled

	if (cgs.teamLastChatPos != cgs.teamChatPos) {
		if (cg.time - cgs.teamChatMsgTimes[cgs.teamLastChatPos % chatHeight] > cg_teamChatTime.integer) {
			cgs.teamLastChatPos++;
		}

		h = (cgs.teamChatPos - cgs.teamLastChatPos) * TINYCHAR_HEIGHT;

		if ( cgs.clientinfo[cg.clientNum].team == TEAM_RED ) {
			hcolor[0] = cg_redteam_r.value / 255.0;
			hcolor[1] = cg_redteam_g.value / 255.0;
			hcolor[2] = cg_redteam_b.value / 255.0;
			hcolor[3] = 0.33f;
		} else if ( cgs.clientinfo[cg.clientNum].team == TEAM_BLUE ) {
			hcolor[0] = cg_blueteam_r.value / 255.0;
			hcolor[1] = cg_blueteam_g.value / 255.0;
			hcolor[2] = cg_blueteam_b.value / 255.0;
			hcolor[3] = 0.33f;
		} else {
			hcolor[0] = 0.0f;
			hcolor[1] = 1.0f;
			hcolor[2] = 0.0f;
			hcolor[3] = 0.33f;
		}

		trap_R_SetColor( hcolor );
		CG_DrawPic( CHATLOC_X, CHATLOC_Y - h, 640, h, cgs.media.teamStatusBar );
		trap_R_SetColor( NULL );

		hcolor[0] = hcolor[1] = hcolor[2] = 1.0f;
		hcolor[3] = 1.0f;

		for (i = cgs.teamChatPos - 1; i >= cgs.teamLastChatPos; i--) {
			CG_DrawStringExt( CHATLOC_X + TINYCHAR_WIDTH, 
				CHATLOC_Y - (cgs.teamChatPos - i)*TINYCHAR_HEIGHT, 
				cgs.teamChatMsgs[i % chatHeight], hcolor, qfalse, qfalse,
				TINYCHAR_WIDTH, TINYCHAR_HEIGHT, 0 );
		}
	}
}
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
typedef  int /*<<< orphan*/  qboolean ;

/* Variables and functions */
#define  UI_BLUETEAM1 154 
#define  UI_BLUETEAM2 153 
#define  UI_BLUETEAM3 152 
#define  UI_BLUETEAM4 151 
#define  UI_BLUETEAM5 150 
#define  UI_BLUETEAMNAME 149 
#define  UI_BOTNAME 148 
#define  UI_BOTSKILL 147 
 int /*<<< orphan*/  UI_BotName_HandleKey (int,float*,int) ; 
 int /*<<< orphan*/  UI_BotSkill_HandleKey (int,float*,int) ; 
#define  UI_CLANNAME 146 
#define  UI_CROSSHAIR 145 
 int /*<<< orphan*/  UI_ClanName_HandleKey (int,float*,int) ; 
 int /*<<< orphan*/  UI_Crosshair_HandleKey (int,float*,int) ; 
#define  UI_EFFECTS 144 
 int /*<<< orphan*/  UI_Effects_HandleKey (int,float*,int) ; 
#define  UI_GAMETYPE 143 
 int /*<<< orphan*/  UI_GameType_HandleKey (int,float*,int,int /*<<< orphan*/ ) ; 
#define  UI_HANDICAP 142 
 int /*<<< orphan*/  UI_Handicap_HandleKey (int,float*,int) ; 
#define  UI_JOINGAMETYPE 141 
 int /*<<< orphan*/  UI_JoinGameType_HandleKey (int,float*,int) ; 
#define  UI_NETFILTER 140 
#define  UI_NETGAMETYPE 139 
#define  UI_NETSOURCE 138 
 int /*<<< orphan*/  UI_NetFilter_HandleKey (int,float*,int) ; 
 int /*<<< orphan*/  UI_NetGameType_HandleKey (int,float*,int) ; 
 int /*<<< orphan*/  UI_NetSource_HandleKey (int,float*,int) ; 
#define  UI_OPPONENT_NAME 137 
 int /*<<< orphan*/  UI_OpponentName_HandleKey (int,float*,int) ; 
#define  UI_REDBLUE 136 
#define  UI_REDTEAM1 135 
#define  UI_REDTEAM2 134 
#define  UI_REDTEAM3 133 
#define  UI_REDTEAM4 132 
#define  UI_REDTEAM5 131 
#define  UI_REDTEAMNAME 130 
 int /*<<< orphan*/  UI_RedBlue_HandleKey (int,float*,int) ; 
#define  UI_SELECTEDPLAYER 129 
#define  UI_SKILL 128 
 int /*<<< orphan*/  UI_SelectedPlayer_HandleKey (int,float*,int) ; 
 int /*<<< orphan*/  UI_Skill_HandleKey (int,float*,int) ; 
 int /*<<< orphan*/  UI_TeamMember_HandleKey (int,float*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_TeamName_HandleKey (int,float*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

__attribute__((used)) static qboolean UI_OwnerDrawHandleKey(int ownerDraw, int flags, float *special, int key) {
  switch (ownerDraw) {
    case UI_HANDICAP:
      return UI_Handicap_HandleKey(flags, special, key);
      break;
    case UI_EFFECTS:
      return UI_Effects_HandleKey(flags, special, key);
      break;
    case UI_CLANNAME:
      return UI_ClanName_HandleKey(flags, special, key);
      break;
    case UI_GAMETYPE:
      return UI_GameType_HandleKey(flags, special, key, qtrue);
      break;
    case UI_NETGAMETYPE:
      return UI_NetGameType_HandleKey(flags, special, key);
      break;
    case UI_JOINGAMETYPE:
      return UI_JoinGameType_HandleKey(flags, special, key);
      break;
    case UI_SKILL:
      return UI_Skill_HandleKey(flags, special, key);
      break;
    case UI_BLUETEAMNAME:
      return UI_TeamName_HandleKey(flags, special, key, qtrue);
      break;
    case UI_REDTEAMNAME:
      return UI_TeamName_HandleKey(flags, special, key, qfalse);
      break;
    case UI_BLUETEAM1:
		case UI_BLUETEAM2:
		case UI_BLUETEAM3:
		case UI_BLUETEAM4:
		case UI_BLUETEAM5:
      UI_TeamMember_HandleKey(flags, special, key, qtrue, ownerDraw - UI_BLUETEAM1 + 1);
      break;
    case UI_REDTEAM1:
		case UI_REDTEAM2:
		case UI_REDTEAM3:
		case UI_REDTEAM4:
		case UI_REDTEAM5:
      UI_TeamMember_HandleKey(flags, special, key, qfalse, ownerDraw - UI_REDTEAM1 + 1);
      break;
		case UI_NETSOURCE:
      UI_NetSource_HandleKey(flags, special, key);
			break;
		case UI_NETFILTER:
      UI_NetFilter_HandleKey(flags, special, key);
			break;
		case UI_OPPONENT_NAME:
			UI_OpponentName_HandleKey(flags, special, key);
			break;
		case UI_BOTNAME:
			return UI_BotName_HandleKey(flags, special, key);
			break;
		case UI_BOTSKILL:
			return UI_BotSkill_HandleKey(flags, special, key);
			break;
		case UI_REDBLUE:
			UI_RedBlue_HandleKey(flags, special, key);
			break;
		case UI_CROSSHAIR:
			UI_Crosshair_HandleKey(flags, special, key);
			break;
		case UI_SELECTEDPLAYER:
			UI_SelectedPlayer_HandleKey(flags, special, key);
			break;
    default:
      break;
  }

  return qfalse;
}
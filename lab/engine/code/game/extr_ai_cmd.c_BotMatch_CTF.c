#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  netname ;
typedef  int /*<<< orphan*/  flag ;
struct TYPE_7__ {int redflagstatus; int blueflagstatus; int flagstatuschanged; void* flagcarrier; int /*<<< orphan*/  lastflagcapture_time; } ;
typedef  TYPE_1__ bot_state_t ;
struct TYPE_8__ {int subtype; } ;
typedef  TYPE_2__ bot_match_t ;

/* Variables and functions */
 scalar_t__ BotTeam (TYPE_1__*) ; 
 void* ClientFromName (char*) ; 
 int /*<<< orphan*/  FLAG ; 
 int /*<<< orphan*/  FloatTime () ; 
 scalar_t__ GT_1FCTF ; 
 scalar_t__ GT_CTF ; 
 int MAX_NETNAME ; 
 int /*<<< orphan*/  NETNAME ; 
 int /*<<< orphan*/  Q_stricmp (char*,char*) ; 
 int ST_1FCTFGOTFLAG ; 
 int ST_CAPTUREDFLAG ; 
 int ST_GOTFLAG ; 
 int ST_RETURNEDFLAG ; 
 scalar_t__ TEAM_BLUE ; 
 scalar_t__ TEAM_RED ; 
 scalar_t__ gametype ; 
 int /*<<< orphan*/  trap_BotMatchVariable (TYPE_2__*,int /*<<< orphan*/ ,char*,int) ; 

void BotMatch_CTF(bot_state_t *bs, bot_match_t *match) {

	char flag[128], netname[MAX_NETNAME];

	if (gametype == GT_CTF) {
		trap_BotMatchVariable(match, FLAG, flag, sizeof(flag));
		if (match->subtype & ST_GOTFLAG) {
			if (!Q_stricmp(flag, "red")) {
				bs->redflagstatus = 1;
				if (BotTeam(bs) == TEAM_BLUE) {
					trap_BotMatchVariable(match, NETNAME, netname, sizeof(netname));
					bs->flagcarrier = ClientFromName(netname);
				}
			}
			else {
				bs->blueflagstatus = 1;
				if (BotTeam(bs) == TEAM_RED) {
					trap_BotMatchVariable(match, NETNAME, netname, sizeof(netname));
					bs->flagcarrier = ClientFromName(netname);
				}
			}
			bs->flagstatuschanged = 1;
			bs->lastflagcapture_time = FloatTime();
		}
		else if (match->subtype & ST_CAPTUREDFLAG) {
			bs->redflagstatus = 0;
			bs->blueflagstatus = 0;
			bs->flagcarrier = 0;
			bs->flagstatuschanged = 1;
		}
		else if (match->subtype & ST_RETURNEDFLAG) {
			if (!Q_stricmp(flag, "red")) bs->redflagstatus = 0;
			else bs->blueflagstatus = 0;
			bs->flagstatuschanged = 1;
		}
	}
#ifdef MISSIONPACK
	else if (gametype == GT_1FCTF) {
		if (match->subtype & ST_1FCTFGOTFLAG) {
			trap_BotMatchVariable(match, NETNAME, netname, sizeof(netname));
			bs->flagcarrier = ClientFromName(netname);
		}
	}
#endif
}
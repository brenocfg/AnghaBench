#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_5__* client; } ;
typedef  TYPE_6__ gentity_t ;
struct TYPE_16__ {int /*<<< orphan*/  time; } ;
struct TYPE_12__ {int /*<<< orphan*/  lasthurtcarrier; } ;
struct TYPE_13__ {TYPE_3__ teamState; } ;
struct TYPE_11__ {scalar_t__ sessionTeam; } ;
struct TYPE_10__ {scalar_t__ generic1; scalar_t__* powerups; } ;
struct TYPE_14__ {TYPE_4__ pers; TYPE_2__ sess; TYPE_1__ ps; } ;

/* Variables and functions */
 int PW_BLUEFLAG ; 
 int PW_REDFLAG ; 
 scalar_t__ TEAM_RED ; 
 TYPE_7__ level ; 

void Team_CheckHurtCarrier(gentity_t *targ, gentity_t *attacker)
{
	int flag_pw;

	if (!targ->client || !attacker->client)
		return;

	if (targ->client->sess.sessionTeam == TEAM_RED)
		flag_pw = PW_BLUEFLAG;
	else
		flag_pw = PW_REDFLAG;

#ifdef MISSIONPACK
	if (g_gametype.integer == GT_1FCTF) {
		flag_pw = PW_NEUTRALFLAG;
	}
#endif

	// flags
	if (targ->client->ps.powerups[flag_pw] &&
		targ->client->sess.sessionTeam != attacker->client->sess.sessionTeam)
		attacker->client->pers.teamState.lasthurtcarrier = level.time;

	// skulls
	if (targ->client->ps.generic1 &&
		targ->client->sess.sessionTeam != attacker->client->sess.sessionTeam)
		attacker->client->pers.teamState.lasthurtcarrier = level.time;
}
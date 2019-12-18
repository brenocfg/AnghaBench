#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ team_t ;
struct TYPE_6__ {size_t client; } ;
typedef  TYPE_1__ score_t ;
struct TYPE_7__ {scalar_t__ team; } ;
typedef  TYPE_2__ clientInfo_t ;
struct TYPE_9__ {int numScores; TYPE_1__* scores; } ;
struct TYPE_8__ {TYPE_2__* clientinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_DrawClientScore (int,TYPE_1__*,float*,float,int) ; 
 int SB_NORMAL_HEIGHT ; 
 TYPE_4__ cg ; 
 TYPE_3__ cgs ; 

__attribute__((used)) static int CG_TeamScoreboard( int y, team_t team, float fade, int maxClients, int lineHeight ) {
	int		i;
	score_t	*score;
	float	color[4];
	int		count;
	clientInfo_t	*ci;

	color[0] = color[1] = color[2] = 1.0;
	color[3] = fade;

	count = 0;
	for ( i = 0 ; i < cg.numScores && count < maxClients ; i++ ) {
		score = &cg.scores[i];
		ci = &cgs.clientinfo[ score->client ];

		if ( team != ci->team ) {
			continue;
		}

		CG_DrawClientScore( y + lineHeight * count, score, color, fade, lineHeight == SB_NORMAL_HEIGHT );

		count++;
	}

	return count;
}
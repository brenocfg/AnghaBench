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
struct TYPE_4__ {void* warmup; } ;
struct TYPE_3__ {scalar_t__ gametype; char redflag; char blueflag; char flagStatus; void* levelStartTime; void* scores2; void* scores1; } ;

/* Variables and functions */
 char* CG_ConfigString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CS_FLAGSTATUS ; 
 int /*<<< orphan*/  CS_LEVEL_START_TIME ; 
 int /*<<< orphan*/  CS_SCORES1 ; 
 int /*<<< orphan*/  CS_SCORES2 ; 
 int /*<<< orphan*/  CS_WARMUP ; 
 scalar_t__ GT_1FCTF ; 
 scalar_t__ GT_CTF ; 
 void* atoi (char*) ; 
 TYPE_2__ cg ; 
 TYPE_1__ cgs ; 

void CG_SetConfigValues( void ) {
	const char *s;

	cgs.scores1 = atoi( CG_ConfigString( CS_SCORES1 ) );
	cgs.scores2 = atoi( CG_ConfigString( CS_SCORES2 ) );
	cgs.levelStartTime = atoi( CG_ConfigString( CS_LEVEL_START_TIME ) );
	if( cgs.gametype == GT_CTF ) {
		s = CG_ConfigString( CS_FLAGSTATUS );
		cgs.redflag = s[0] - '0';
		cgs.blueflag = s[1] - '0';
	}
#ifdef MISSIONPACK
	else if( cgs.gametype == GT_1FCTF ) {
		s = CG_ConfigString( CS_FLAGSTATUS );
		cgs.flagStatus = s[0] - '0';
	}
#endif
	cg.warmup = atoi( CG_ConfigString( CS_WARMUP ) );
}
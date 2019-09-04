#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  netadr_t ;
struct TYPE_5__ {int challenge; int /*<<< orphan*/  adr; int /*<<< orphan*/  clientChallenge; int /*<<< orphan*/  pingTime; } ;
typedef  TYPE_1__ challenge_t ;
struct TYPE_7__ {int /*<<< orphan*/  integer; } ;
struct TYPE_6__ {int /*<<< orphan*/  time; TYPE_1__* challenges; int /*<<< orphan*/  authorizeAddress; } ;

/* Variables and functions */
 char* Cmd_Argv (int) ; 
 int /*<<< orphan*/  Com_Memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Com_Printf (char*) ; 
 int MAX_CHALLENGES ; 
 int /*<<< orphan*/  NET_CompareBaseAdr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NET_OutOfBandPrint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  NS_SERVER ; 
 int /*<<< orphan*/  Q_stricmp (char*,char*) ; 
 int atoi (char*) ; 
 TYPE_3__* com_protocol ; 
 TYPE_2__ svs ; 

void SV_AuthorizeIpPacket( netadr_t from ) {
	int		challenge;
	int		i;
	char	*s;
	char	*r;
	challenge_t *challengeptr;

	if ( !NET_CompareBaseAdr( from, svs.authorizeAddress ) ) {
		Com_Printf( "SV_AuthorizeIpPacket: not from authorize server\n" );
		return;
	}

	challenge = atoi( Cmd_Argv( 1 ) );

	for (i = 0 ; i < MAX_CHALLENGES ; i++) {
		if ( svs.challenges[i].challenge == challenge ) {
			break;
		}
	}
	if ( i == MAX_CHALLENGES ) {
		Com_Printf( "SV_AuthorizeIpPacket: challenge not found\n" );
		return;
	}
	
	challengeptr = &svs.challenges[i];

	// send a packet back to the original client
	challengeptr->pingTime = svs.time;
	s = Cmd_Argv( 2 );
	r = Cmd_Argv( 3 );			// reason

	if ( !Q_stricmp( s, "demo" ) ) {
		// they are a demo client trying to connect to a real server
		NET_OutOfBandPrint( NS_SERVER, challengeptr->adr, "print\nServer is not a demo server\n" );
		// clear the challenge record so it won't timeout and let them through
		Com_Memset( challengeptr, 0, sizeof( *challengeptr ) );
		return;
	}
	if ( !Q_stricmp( s, "accept" ) ) {
		NET_OutOfBandPrint(NS_SERVER, challengeptr->adr,
			"challengeResponse %d %d %d", challengeptr->challenge, challengeptr->clientChallenge, com_protocol->integer);
		return;
	}
	if ( !Q_stricmp( s, "unknown" ) ) {
		if (!r) {
			NET_OutOfBandPrint( NS_SERVER, challengeptr->adr, "print\nAwaiting CD key authorization\n" );
		} else {
			NET_OutOfBandPrint( NS_SERVER, challengeptr->adr, "print\n%s\n", r);
		}
		// clear the challenge record so it won't timeout and let them through
		Com_Memset( challengeptr, 0, sizeof( *challengeptr ) );
		return;
	}

	// authorization failed
	if (!r) {
		NET_OutOfBandPrint( NS_SERVER, challengeptr->adr, "print\nSomeone is using this CD Key\n" );
	} else {
		NET_OutOfBandPrint( NS_SERVER, challengeptr->adr, "print\n%s\n", r );
	}

	// clear the challenge record so it won't timeout and let them through
	Com_Memset( challengeptr, 0, sizeof(*challengeptr) );
}
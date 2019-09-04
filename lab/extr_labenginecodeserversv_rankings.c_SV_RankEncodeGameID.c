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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  qint64 ;
typedef  int /*<<< orphan*/  game_id ;

/* Variables and functions */
 int /*<<< orphan*/  Com_DPrintf (char*) ; 
 int /*<<< orphan*/  LittleLong64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SV_RankAsciiEncode (char*,unsigned char*,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void SV_RankEncodeGameID( uint64_t game_id, char* result, 
	int len )
{
	assert( result != NULL );

	if( len < ( ( sizeof(game_id) * 4) / 3 + 2) )
	{
		Com_DPrintf( "SV_RankEncodeGameID: result buffer too small\n" );
		result[0] = '\0';
	}
	else
	{
		qint64 gameid = LittleLong64(*(qint64*)&game_id);
		SV_RankAsciiEncode( result, (unsigned char*)&gameid, 
			sizeof(qint64) );
	}
}
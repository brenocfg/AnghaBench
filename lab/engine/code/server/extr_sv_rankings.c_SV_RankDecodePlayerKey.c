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
typedef  int /*<<< orphan*/  buffer ;
typedef  unsigned char* GR_PLAYER_TOKEN ;

/* Variables and functions */
 int /*<<< orphan*/  Com_DPrintf (char*,int) ; 
 int /*<<< orphan*/  SV_RankAsciiDecode (unsigned char*,char const*,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void SV_RankDecodePlayerKey( const char* string, GR_PLAYER_TOKEN key )
{
	unsigned char	buffer[1400];
	int len;
	assert( string != NULL );

	len = strlen (string) ;
	Com_DPrintf( "SV_RankDecodePlayerKey: string length %d\n",len );
	
	memset(key,0,sizeof(GR_PLAYER_TOKEN));
	memset(buffer,0,sizeof(buffer));
	memcpy( key, buffer, SV_RankAsciiDecode( buffer, string, len ) );
}
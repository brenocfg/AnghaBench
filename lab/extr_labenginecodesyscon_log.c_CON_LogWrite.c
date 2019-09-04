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

/* Variables and functions */
 unsigned int CON_LogFree () ; 
 int CON_LogSize () ; 
 int /*<<< orphan*/  Com_Memcpy (char*,char const*,unsigned int) ; 
 size_t MAX_LOG ; 
 char* consoleLog ; 
 size_t readPos ; 
 unsigned int strlen (char const*) ; 
 unsigned int writePos ; 

unsigned int CON_LogWrite( const char *in )
{
	unsigned int length = strlen( in );
	unsigned int firstChunk;
	unsigned int secondChunk;

	while( CON_LogFree( ) < length && CON_LogSize( ) > 0 )
	{
		// Free enough space
		while( consoleLog[ readPos ] != '\n' && CON_LogSize( ) > 1 )
			readPos = ( readPos + 1 ) % MAX_LOG;

		// Skip past the '\n'
		readPos = ( readPos + 1 ) % MAX_LOG;
	}

	if( CON_LogFree( ) < length )
		return 0;

	if( writePos + length > MAX_LOG )
	{
		firstChunk  = MAX_LOG - writePos;
		secondChunk = length - firstChunk;
	}
	else
	{
		firstChunk  = length;
		secondChunk = 0;
	}

	Com_Memcpy( consoleLog + writePos, in, firstChunk );
	Com_Memcpy( consoleLog, in + firstChunk, secondChunk );

	writePos = ( writePos + length ) % MAX_LOG;

	return length;
}
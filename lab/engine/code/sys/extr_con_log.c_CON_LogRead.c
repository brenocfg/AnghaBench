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
 unsigned int CON_LogSize () ; 
 int /*<<< orphan*/  Com_Memcpy (char*,scalar_t__,unsigned int) ; 
 unsigned int MAX_LOG ; 
 scalar_t__ consoleLog ; 
 unsigned int readPos ; 

unsigned int CON_LogRead( char *out, unsigned int outSize )
{
	unsigned int firstChunk;
	unsigned int secondChunk;

	if( CON_LogSize( ) < outSize )
		outSize = CON_LogSize( );

	if( readPos + outSize > MAX_LOG )
	{
		firstChunk  = MAX_LOG - readPos;
		secondChunk = outSize - firstChunk;
	}
	else
	{
		firstChunk  = outSize;
		secondChunk = 0;
	}

	Com_Memcpy( out, consoleLog + readPos, firstChunk );
	Com_Memcpy( out + firstChunk, consoleLog, secondChunk );

	readPos = ( readPos + outSize ) % MAX_LOG;

	return outSize;
}
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
typedef  int /*<<< orphan*/  s_userName ;

/* Variables and functions */
 int /*<<< orphan*/  GetUserName (char*,unsigned long*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

char *Sys_GetCurrentUser( void )
{
	static char s_userName[1024];
	unsigned long size = sizeof( s_userName );

	if( !GetUserName( s_userName, &size ) )
		strcpy( s_userName, "player" );

	if( !s_userName[0] )
	{
		strcpy( s_userName, "player" );
	}

	return s_userName;
}
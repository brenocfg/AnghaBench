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
 int /*<<< orphan*/  Q_strcat (char*,int,char const*) ; 
 int /*<<< orphan*/  Q_strncpyz (char*,char const*,int) ; 
 int TRUNCATE_LENGTH ; 
 int strlen (char const*) ; 

void Com_TruncateLongString( char *buffer, const char *s )
{
	int length = strlen( s );

	if( length <= TRUNCATE_LENGTH )
		Q_strncpyz( buffer, s, TRUNCATE_LENGTH );
	else
	{
		Q_strncpyz( buffer, s, ( TRUNCATE_LENGTH / 2 ) - 3 );
		Q_strcat( buffer, TRUNCATE_LENGTH, " ... " );
		Q_strcat( buffer, TRUNCATE_LENGTH, s + length - ( TRUNCATE_LENGTH / 2 ) + 3 );
	}
}
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
typedef  int /*<<< orphan*/  qboolean ;

/* Variables and functions */
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean Com_PlayerNameToFieldString( char *str, int length, const char *name )
{
	const char *p;
	int i;
	int x1, x2;

	if( str == NULL || name == NULL )
		return qfalse;

	if( length <= 0 )
		return qtrue;

	*str = '\0';
	p = name;

	for( i = 0; *p != '\0'; i++, p++ )
	{
		if( i + 1 >= length )
			break;

		if( *p <= ' ' )
		{
			if( i + 5 + 1 >= length )
				break;

			x1 = *p >> 4;
			x2 = *p & 15;

			str[i+0] = '\\';
			str[i+1] = '0';
			str[i+2] = 'x';
			str[i+3] = x1 > 9 ? x1 - 10 + 'a' : x1 + '0';
			str[i+4] = x2 > 9 ? x2 - 10 + 'a' : x2 + '0';

			i += 4;
		} else {
			str[i] = *p;
		}		
	}
	str[i] = '\0';

	return qtrue;
}
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
typedef  int /*<<< orphan*/  val ;

/* Variables and functions */
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,float) ; 
 int /*<<< orphan*/  Cvar_SetSafe (char const*,char*) ; 
 scalar_t__ Q_isintegral (float) ; 

void Cvar_SetValueSafe( const char *var_name, float value )
{
	char val[32];

	if( Q_isintegral( value ) )
		Com_sprintf( val, sizeof(val), "%i", (int)value );
	else
		Com_sprintf( val, sizeof(val), "%f", value );
	Cvar_SetSafe( var_name, val );
}
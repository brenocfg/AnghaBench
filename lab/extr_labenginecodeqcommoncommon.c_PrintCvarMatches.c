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
 int /*<<< orphan*/  Com_Printf (char*,char const*,char*) ; 
 int /*<<< orphan*/  Com_TruncateLongString (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cvar_VariableString (char const*) ; 
 int /*<<< orphan*/  Q_stricmpn (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TRUNCATE_LENGTH ; 
 int /*<<< orphan*/  shortestMatch ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void PrintCvarMatches( const char *s ) {
	char value[ TRUNCATE_LENGTH ];

	if ( !Q_stricmpn( s, shortestMatch, strlen( shortestMatch ) ) ) {
		Com_TruncateLongString( value, Cvar_VariableString( s ) );
		Com_Printf( "    %s = \"%s\"\n", s, value );
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* qboolean ;
struct TYPE_2__ {int* script_p; int* end_p; scalar_t__ line; int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddScriptToStack (char*,int /*<<< orphan*/ ) ; 
 void* EndOfScript (void*) ; 
 int /*<<< orphan*/  Error (char*,scalar_t__) ; 
 size_t MAXTOKEN ; 
 void* qfalse ; 
 void* qtrue ; 
 TYPE_1__* script ; 
 scalar_t__ scriptline ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* token ; 
 void* tokenready ; 

qboolean GetToken( qboolean crossline ){
	char    *token_p;


	/* ydnar: dummy testing */
	if ( script == NULL || script->buffer == NULL ) {
		return qfalse;
	}

	if ( tokenready ) {                       // is a token already waiting?
		tokenready = qfalse;
		return qtrue;
	}

	if ( ( script->script_p >= script->end_p ) || ( script->script_p == NULL ) ) {
		return EndOfScript( crossline );
	}

//
// skip space
//
skipspace:
	while ( *script->script_p <= 32 )
	{
		if ( script->script_p >= script->end_p ) {
			return EndOfScript( crossline );
		}
		if ( *script->script_p++ == '\n' ) {
			if ( !crossline ) {
				Error( "Line %i is incomplete\n",scriptline );
			}
			script->line++;
			scriptline = script->line;
		}
	}

	if ( script->script_p >= script->end_p ) {
		return EndOfScript( crossline );
	}

	// ; # // comments
	if ( *script->script_p == ';' || *script->script_p == '#'
		 || ( script->script_p[0] == '/' && script->script_p[1] == '/' ) ) {
		if ( !crossline ) {
			Error( "Line %i is incomplete\n",scriptline );
		}
		while ( *script->script_p++ != '\n' )
			if ( script->script_p >= script->end_p ) {
				return EndOfScript( crossline );
			}
		script->line++;
		scriptline = script->line;
		goto skipspace;
	}

	// /* */ comments
	if ( script->script_p[0] == '/' && script->script_p[1] == '*' ) {
		if ( !crossline ) {
			Error( "Line %i is incomplete\n",scriptline );
		}
		script->script_p += 2;
		while ( script->script_p[0] != '*' && script->script_p[1] != '/' )
		{
			if ( *script->script_p == '\n' ) {
				script->line++;
				scriptline = script->line;
			}
			script->script_p++;
			if ( script->script_p >= script->end_p ) {
				return EndOfScript( crossline );
			}
		}
		script->script_p += 2;
		goto skipspace;
	}

//
// copy token
//
	token_p = token;

	if ( *script->script_p == '"' ) {
		// quoted token
		script->script_p++;
		while ( *script->script_p != '"' )
		{
			*token_p++ = *script->script_p++;
			if ( script->script_p == script->end_p ) {
				break;
			}
			if ( token_p == &token[MAXTOKEN] ) {
				Error( "Token too large on line %i\n",scriptline );
			}
		}
		script->script_p++;
	}
	else{   // regular token
		while ( *script->script_p > 32 && *script->script_p != ';' )
		{
			*token_p++ = *script->script_p++;
			if ( script->script_p == script->end_p ) {
				break;
			}
			if ( token_p == &token[MAXTOKEN] ) {
				Error( "Token too large on line %i\n",scriptline );
			}
		}
	}

	*token_p = 0;

	if ( !strcmp( token, "$include" ) ) {
		GetToken( qfalse );
		AddScriptToStack( token, 0 );
		return GetToken( crossline );
	}

	return qtrue;
}
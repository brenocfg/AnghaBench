#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  script ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_3__ {char* string; } ;
typedef  TYPE_1__ pc_token_t ;

/* Variables and functions */
 int /*<<< orphan*/  Q_strcat (char*,int,char*) ; 
 scalar_t__ Q_stricmp (char*,char*) ; 
 char* String_Alloc (char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  trap_PC_ReadToken (int,TYPE_1__*) ; 
 char* va (char*,char*) ; 

qboolean PC_Script_Parse(int handle, const char **out) {
	char script[1024];
	pc_token_t token;

	memset(script, 0, sizeof(script));
	// scripts start with { and have ; separated command lists.. commands are command, arg.. 
	// basically we want everything between the { } as it will be interpreted at run time
  
	if (!trap_PC_ReadToken(handle, &token))
		return qfalse;
	if (Q_stricmp(token.string, "{") != 0) {
	    return qfalse;
	}

	while ( 1 ) {
		if (!trap_PC_ReadToken(handle, &token))
			return qfalse;

		if (Q_stricmp(token.string, "}") == 0) {
			*out = String_Alloc(script);
			return qtrue;
		}

		if (token.string[1] != '\0') {
			Q_strcat(script, 1024, va("\"%s\"", token.string));
		} else {
			Q_strcat(script, 1024, token.string);
		}
		Q_strcat(script, 1024, " ");
	}
	return qfalse;
}
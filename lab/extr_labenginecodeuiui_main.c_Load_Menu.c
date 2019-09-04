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
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_3__ {char* string; } ;
typedef  TYPE_1__ pc_token_t ;

/* Variables and functions */
 int /*<<< orphan*/  UI_ParseMenu (char*) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  trap_PC_ReadToken (int,TYPE_1__*) ; 

qboolean Load_Menu(int handle) {
	pc_token_t token;

	if (!trap_PC_ReadToken(handle, &token))
		return qfalse;
	if (token.string[0] != '{') {
		return qfalse;
	}

	while ( 1 ) {

		if (!trap_PC_ReadToken(handle, &token))
			return qfalse;
    
		if ( token.string[0] == 0 ) {
			return qfalse;
		}

		if ( token.string[0] == '}' ) {
			return qtrue;
		}

		UI_ParseMenu(token.string); 
	}
	return qfalse;
}
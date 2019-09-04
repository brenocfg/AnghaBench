#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_6__ {char* string; } ;
typedef  TYPE_1__ pc_token_t ;
typedef  int /*<<< orphan*/  menuDef_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ *,int) ;} ;
typedef  TYPE_2__ keywordHash_t ;
typedef  int /*<<< orphan*/  itemDef_t ;

/* Variables and functions */
 TYPE_2__* KeywordHash_Find (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PC_SourceError (int,char*,...) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  menuParseKeywordHash ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trap_PC_ReadToken (int,TYPE_1__*) ; 

qboolean Menu_Parse(int handle, menuDef_t *menu) {
	pc_token_t token;
	keywordHash_t *key;

	if (!trap_PC_ReadToken(handle, &token))
		return qfalse;
	if (*token.string != '{') {
		return qfalse;
	}
    
	while ( 1 ) {

		memset(&token, 0, sizeof(pc_token_t));
		if (!trap_PC_ReadToken(handle, &token)) {
			PC_SourceError(handle, "end of file inside menu");
			return qfalse;
		}

		if (*token.string == '}') {
			return qtrue;
		}

		key = KeywordHash_Find(menuParseKeywordHash, token.string);
		if (!key) {
			PC_SourceError(handle, "unknown menu keyword %s", token.string);
			continue;
		}
		if ( !key->func((itemDef_t*)menu, handle) ) {
			PC_SourceError(handle, "couldn't parse menu keyword %s", token.string);
			return qfalse;
		}
	}
	return qfalse;
}
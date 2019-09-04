#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_7__ {char* string; } ;
typedef  TYPE_1__ pc_token_t ;
struct TYPE_8__ {size_t count; int /*<<< orphan*/ * cvarValue; int /*<<< orphan*/ * cvarList; int /*<<< orphan*/  strDef; } ;
typedef  TYPE_2__ multiDef_t ;
struct TYPE_9__ {scalar_t__ typeData; } ;
typedef  TYPE_3__ itemDef_t ;

/* Variables and functions */
 int /*<<< orphan*/  Item_ValidateTypeData (TYPE_3__*) ; 
 size_t MAX_MULTI_CVARS ; 
 int /*<<< orphan*/  PC_Float_Parse (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PC_SourceError (int,char*) ; 
 int /*<<< orphan*/  String_Alloc (char*) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  trap_PC_ReadToken (int,TYPE_1__*) ; 

qboolean ItemParse_cvarFloatList( itemDef_t *item, int handle ) {
	pc_token_t token;
	multiDef_t *multiPtr;
	
	Item_ValidateTypeData(item);
	if (!item->typeData)
		return qfalse;
	multiPtr = (multiDef_t*)item->typeData;
	multiPtr->count = 0;
	multiPtr->strDef = qfalse;

	if (!trap_PC_ReadToken(handle, &token))
		return qfalse;
	if (*token.string != '{') {
		return qfalse;
	}

	while ( 1 ) {
		if (!trap_PC_ReadToken(handle, &token)) {
			PC_SourceError(handle, "end of file inside menu item");
			return qfalse;
		}

		if (*token.string == '}') {
			return qtrue;
		}

		if (*token.string == ',' || *token.string == ';') {
			continue;
		}

		multiPtr->cvarList[multiPtr->count] = String_Alloc(token.string);
		if (!PC_Float_Parse(handle, &multiPtr->cvarValue[multiPtr->count])) {
			return qfalse;
		}

		multiPtr->count++;
		if (multiPtr->count >= MAX_MULTI_CVARS) {
			return qfalse;
		}

	}
	return qfalse;
}
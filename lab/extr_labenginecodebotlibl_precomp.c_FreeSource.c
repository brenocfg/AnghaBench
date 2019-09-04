#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {struct TYPE_11__* next; } ;
typedef  TYPE_1__ token_t ;
struct TYPE_12__ {struct TYPE_12__* next; struct TYPE_12__* indentstack; TYPE_5__* defines; TYPE_1__* tokens; TYPE_3__* scriptstack; } ;
typedef  TYPE_2__ source_t ;
struct TYPE_13__ {struct TYPE_13__* next; } ;
typedef  TYPE_3__ script_t ;
typedef  TYPE_2__ indent_t ;
struct TYPE_14__ {struct TYPE_14__* next; } ;
typedef  TYPE_5__ define_t ;

/* Variables and functions */
 int /*<<< orphan*/  FreeMemory (TYPE_2__*) ; 
 int /*<<< orphan*/  FreeScript (TYPE_3__*) ; 
 int /*<<< orphan*/  PC_FreeDefine (TYPE_5__*) ; 
 int /*<<< orphan*/  PC_FreeToken (TYPE_1__*) ; 

void FreeSource(source_t *source)
{
	script_t *script;
	token_t *token;
	define_t *define;
	indent_t *indent;
	int i;

	//PC_PrintDefineHashTable(source->definehash);
	//free all the scripts
	while(source->scriptstack)
	{
		script = source->scriptstack;
		source->scriptstack = source->scriptstack->next;
		FreeScript(script);
	} //end for
	//free all the tokens
	while(source->tokens)
	{
		token = source->tokens;
		source->tokens = source->tokens->next;
		PC_FreeToken(token);
	} //end for
#if DEFINEHASHING
	for (i = 0; i < DEFINEHASHSIZE; i++)
	{
		while(source->definehash[i])
		{
			define = source->definehash[i];
			source->definehash[i] = source->definehash[i]->hashnext;
			PC_FreeDefine(define);
		} //end while
	} //end for
#else //DEFINEHASHING
	//free all defines
	while(source->defines)
	{
		define = source->defines;
		source->defines = source->defines->next;
		PC_FreeDefine(define);
	} //end for
#endif //DEFINEHASHING
	//free all indents
	while(source->indentstack)
	{
		indent = source->indentstack;
		source->indentstack = source->indentstack->next;
		FreeMemory(indent);
	} //end for
#if DEFINEHASHING
	//
	if (source->definehash) FreeMemory(source->definehash);
#endif //DEFINEHASHING
	//free the source itself
	FreeMemory(source);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int type; int subtype; } ;
typedef  TYPE_1__ token_t ;
typedef  int /*<<< orphan*/  source_t ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  PC_ReadToken (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  PC_UnreadSourceToken (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int qfalse ; 
 int qtrue ; 

int PC_CheckTokenType(source_t *source, int type, int subtype, token_t *token)
{
	token_t tok;

	if (!PC_ReadToken(source, &tok)) return qfalse;
	//if the type matches
	if (tok.type == type &&
			(tok.subtype & subtype) == subtype)
	{
		Com_Memcpy(token, &tok, sizeof(token_t));
		return qtrue;
	} //end if
	//
	PC_UnreadSourceToken(source, &tok);
	return qfalse;
}
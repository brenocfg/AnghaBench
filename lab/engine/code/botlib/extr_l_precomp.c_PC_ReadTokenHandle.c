#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  floatvalue; int /*<<< orphan*/  intvalue; int /*<<< orphan*/  subtype; int /*<<< orphan*/  type; int /*<<< orphan*/  string; } ;
typedef  TYPE_1__ token_t ;
struct TYPE_6__ {int /*<<< orphan*/  string; int /*<<< orphan*/  type; int /*<<< orphan*/  floatvalue; int /*<<< orphan*/  intvalue; int /*<<< orphan*/  subtype; } ;
typedef  TYPE_2__ pc_token_t ;

/* Variables and functions */
 int MAX_SOURCEFILES ; 
 int PC_ReadToken (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  StripDoubleQuotes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TT_STRING ; 
 int /*<<< orphan*/ * sourceFiles ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int PC_ReadTokenHandle(int handle, pc_token_t *pc_token)
{
	token_t token;
	int ret;

	if (handle < 1 || handle >= MAX_SOURCEFILES)
		return 0;
	if (!sourceFiles[handle])
		return 0;

	ret = PC_ReadToken(sourceFiles[handle], &token);
	strcpy(pc_token->string, token.string);
	pc_token->type = token.type;
	pc_token->subtype = token.subtype;
	pc_token->intvalue = token.intvalue;
	pc_token->floatvalue = token.floatvalue;
	if (pc_token->type == TT_STRING)
		StripDoubleQuotes(pc_token->string);
	return ret;
}
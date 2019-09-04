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
typedef  int /*<<< orphan*/  source_t ;

/* Variables and functions */
 int /*<<< orphan*/  INDENT_ELIF ; 
 int INDENT_ELSE ; 
 int /*<<< orphan*/  PC_Evaluate (int /*<<< orphan*/ *,long*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PC_PopIndent (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  PC_PushIndent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SourceError (int /*<<< orphan*/ *,char*) ; 
 int qfalse ; 
 int qtrue ; 

int PC_Directive_elif(source_t *source)
{
	signed long int value;
	int type, skip;

	PC_PopIndent(source, &type, &skip);
	if (!type || type == INDENT_ELSE)
	{
		SourceError(source, "misplaced #elif");
		return qfalse;
	} //end if
	if (!PC_Evaluate(source, &value, NULL, qtrue)) return qfalse;
	skip = (value == 0);
	PC_PushIndent(source, INDENT_ELIF, skip);
	return qtrue;
}
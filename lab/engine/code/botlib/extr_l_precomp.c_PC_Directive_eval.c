#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int subtype; int /*<<< orphan*/  type; int /*<<< orphan*/  string; scalar_t__ linescrossed; int /*<<< orphan*/  endwhitespace_p; int /*<<< orphan*/  whitespace_p; int /*<<< orphan*/  line; } ;
typedef  TYPE_2__ token_t ;
struct TYPE_11__ {TYPE_1__* scriptstack; } ;
typedef  TYPE_3__ source_t ;
struct TYPE_9__ {int /*<<< orphan*/  script_p; int /*<<< orphan*/  line; } ;

/* Variables and functions */
 int /*<<< orphan*/  PC_Evaluate (TYPE_3__*,long*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PC_UnreadSourceToken (TYPE_3__*,TYPE_2__*) ; 
 int TT_DECIMAL ; 
 int TT_INTEGER ; 
 int TT_LONG ; 
 int /*<<< orphan*/  TT_NUMBER ; 
 int /*<<< orphan*/  UnreadSignToken (TYPE_3__*) ; 
 int /*<<< orphan*/  labs (long) ; 
 int qfalse ; 
 int qtrue ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int PC_Directive_eval(source_t *source)
{
	signed long int value;
	token_t token;

	if (!PC_Evaluate(source, &value, NULL, qtrue)) return qfalse;
	//
	token.line = source->scriptstack->line;
	token.whitespace_p = source->scriptstack->script_p;
	token.endwhitespace_p = source->scriptstack->script_p;
	token.linescrossed = 0;
	sprintf(token.string, "%ld", labs(value));
	token.type = TT_NUMBER;
	token.subtype = TT_INTEGER|TT_LONG|TT_DECIMAL;
	PC_UnreadSourceToken(source, &token);
	if (value < 0) UnreadSignToken(source);
	return qtrue;
}
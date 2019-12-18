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
struct TYPE_10__ {int subtype; double floatvalue; unsigned long intvalue; int /*<<< orphan*/  type; int /*<<< orphan*/  string; scalar_t__ linescrossed; int /*<<< orphan*/  endwhitespace_p; int /*<<< orphan*/  whitespace_p; int /*<<< orphan*/  line; } ;
typedef  TYPE_2__ token_t ;
struct TYPE_11__ {TYPE_1__* scriptstack; } ;
typedef  TYPE_3__ source_t ;
struct TYPE_9__ {int /*<<< orphan*/  script_p; int /*<<< orphan*/  line; } ;

/* Variables and functions */
 int /*<<< orphan*/  PC_DollarEvaluate (TYPE_3__*,int /*<<< orphan*/ *,float*,int) ; 
 int /*<<< orphan*/  PC_UnreadSourceToken (TYPE_3__*,TYPE_2__*) ; 
 int TT_DECIMAL ; 
 int TT_FLOAT ; 
 int TT_LONG ; 
 int /*<<< orphan*/  TT_NUMBER ; 
 int /*<<< orphan*/  UnreadSignToken (TYPE_3__*) ; 
 double fabs (float) ; 
 int qfalse ; 
 int qtrue ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,double) ; 

int PC_DollarDirective_evalfloat(source_t *source)
{
	float value;
	token_t token;

	if (!PC_DollarEvaluate(source, NULL, &value, qfalse)) return qfalse;
	token.line = source->scriptstack->line;
	token.whitespace_p = source->scriptstack->script_p;
	token.endwhitespace_p = source->scriptstack->script_p;
	token.linescrossed = 0;
	sprintf(token.string, "%1.2f", fabs(value));
	token.type = TT_NUMBER;
	token.subtype = TT_FLOAT|TT_LONG|TT_DECIMAL;

#ifdef NUMBERVALUE
	token.floatvalue = fabs(value);
	token.intvalue = (unsigned long) token.floatvalue;
#endif //NUMBERVALUE

	PC_UnreadSourceToken(source, &token);
	if (value < 0)
		UnreadSignToken(source);

	return qtrue;
}
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
struct TYPE_8__ {int /*<<< orphan*/  subtype; int /*<<< orphan*/  type; int /*<<< orphan*/  string; scalar_t__ linescrossed; int /*<<< orphan*/  endwhitespace_p; int /*<<< orphan*/  whitespace_p; int /*<<< orphan*/  line; } ;
typedef  TYPE_2__ token_t ;
struct TYPE_9__ {TYPE_1__* scriptstack; } ;
typedef  TYPE_3__ source_t ;
struct TYPE_7__ {int /*<<< orphan*/  script_p; int /*<<< orphan*/  line; } ;

/* Variables and functions */
 int /*<<< orphan*/  PC_UnreadSourceToken (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  P_SUB ; 
 int /*<<< orphan*/  TT_PUNCTUATION ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

void UnreadSignToken(source_t *source)
{
	token_t token;

	token.line = source->scriptstack->line;
	token.whitespace_p = source->scriptstack->script_p;
	token.endwhitespace_p = source->scriptstack->script_p;
	token.linescrossed = 0;
	strcpy(token.string, "-");
	token.type = TT_PUNCTUATION;
	token.subtype = P_SUB;
	PC_UnreadSourceToken(source, &token);
}
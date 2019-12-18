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
typedef  int /*<<< orphan*/  action_text ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAXLINE ; 
 int /*<<< orphan*/  add_action (char*) ; 
 int /*<<< orphan*/  format_pinpoint_message (char*,char*) ; 
 int /*<<< orphan*/  line_directive_out (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  num_eof_rules ; 
 int /*<<< orphan*/  num_rules ; 
 scalar_t__ previous_continued_action ; 
 int* sceof ; 
 char** scname ; 
 size_t* scon_stk ; 
 int scon_stk_ptr ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

void build_eof_action()
	{
	int i;
	char action_text[MAXLINE];

	for ( i = 1; i <= scon_stk_ptr; ++i )
		{
		if ( sceof[scon_stk[i]] )
			format_pinpoint_message(
				"multiple <<EOF>> rules for start condition %s",
				scname[scon_stk[i]] );

		else
			{
			sceof[scon_stk[i]] = true;

			if (previous_continued_action /* && previous action was regular */)
				add_action("YY_RULE_SETUP\n");

			snprintf( action_text, sizeof(action_text), "case YY_STATE_EOF(%s):\n",
				scname[scon_stk[i]] );
			add_action( action_text );
			}
		}

	line_directive_out( (FILE *) 0, 1 );

	/* This isn't a normal rule after all - don't count it as
	 * such, so we don't have any holes in the rule numbering
	 * (which make generating "rule can never match" warnings
	 * more difficult.
	 */
	--num_rules;
	++num_eof_rules;
	}
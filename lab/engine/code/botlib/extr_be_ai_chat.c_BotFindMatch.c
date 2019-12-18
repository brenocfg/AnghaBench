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
struct TYPE_8__ {unsigned long context; int /*<<< orphan*/  subtype; int /*<<< orphan*/  type; int /*<<< orphan*/  first; struct TYPE_8__* next; } ;
typedef  TYPE_2__ bot_matchtemplate_t ;
struct TYPE_9__ {char* string; int /*<<< orphan*/  subtype; int /*<<< orphan*/  type; TYPE_1__* variables; } ;
typedef  TYPE_3__ bot_match_t ;
struct TYPE_7__ {int offset; } ;

/* Variables and functions */
 int MAX_MATCHVARIABLES ; 
 int /*<<< orphan*/  MAX_MESSAGE_SIZE ; 
 int /*<<< orphan*/  Q_strncpyz (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ StringsMatch (int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_2__* matchtemplates ; 
 int qfalse ; 
 int qtrue ; 
 int strlen (char*) ; 

int BotFindMatch(char *str, bot_match_t *match, unsigned long int context)
{
	int i;
	bot_matchtemplate_t *ms;

	Q_strncpyz(match->string, str, MAX_MESSAGE_SIZE);
	//remove any trailing enters
	while(strlen(match->string) &&
			match->string[strlen(match->string)-1] == '\n')
	{
		match->string[strlen(match->string)-1] = '\0';
	} //end while
	//compare the string with all the match strings
	for (ms = matchtemplates; ms; ms = ms->next)
	{
		if (!(ms->context & context)) continue;
		//reset the match variable offsets
		for (i = 0; i < MAX_MATCHVARIABLES; i++) match->variables[i].offset = -1;
		//
		if (StringsMatch(ms->first, match))
		{
			match->type = ms->type;
			match->subtype = ms->subtype;
			return qtrue;
		} //end if
	} //end for
	return qfalse;
}
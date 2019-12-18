#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int flags; char* string; int /*<<< orphan*/  match; struct TYPE_17__* next; } ;
typedef  TYPE_2__ bot_replychatkey_t ;
struct TYPE_18__ {int priority; TYPE_6__* firstchatmessage; TYPE_2__* keys; struct TYPE_18__* next; } ;
typedef  TYPE_3__ bot_replychat_t ;
struct TYPE_19__ {char* string; TYPE_1__* variables; } ;
typedef  TYPE_4__ bot_match_t ;
struct TYPE_20__ {scalar_t__ gender; int /*<<< orphan*/  chatmessage; int /*<<< orphan*/  name; } ;
typedef  TYPE_5__ bot_chatstate_t ;
struct TYPE_21__ {scalar_t__ time; int /*<<< orphan*/  chatmessage; struct TYPE_21__* next; } ;
typedef  TYPE_6__ bot_chatmessage_t ;
struct TYPE_22__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ;} ;
struct TYPE_16__ {int offset; int length; } ;

/* Variables and functions */
 scalar_t__ AAS_Time () ; 
 TYPE_5__* BotChatStateFromHandle (int) ; 
 int /*<<< orphan*/  BotConstructChatMessage (TYPE_5__*,int /*<<< orphan*/ ,int,TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  BotRemoveTildes (int /*<<< orphan*/ ) ; 
 scalar_t__ CHATMESSAGE_RECENTTIME ; 
 scalar_t__ CHAT_GENDERFEMALE ; 
 scalar_t__ CHAT_GENDERLESS ; 
 scalar_t__ CHAT_GENDERMALE ; 
 int /*<<< orphan*/  Com_Memcpy (TYPE_4__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  Com_Memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ LibVarGetValue (char*) ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 int RCKFL_AND ; 
 int RCKFL_BOTNAMES ; 
 int RCKFL_GENDERFEMALE ; 
 int RCKFL_GENDERLESS ; 
 int RCKFL_GENDERMALE ; 
 int RCKFL_NAME ; 
 int RCKFL_NOT ; 
 int RCKFL_STRING ; 
 int RCKFL_VARIABLES ; 
 int StringContains (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * StringContainsWord (char*,char*,int) ; 
 int StringsMatch (int /*<<< orphan*/ ,TYPE_4__*) ; 
 TYPE_8__ botimport ; 
 int qfalse ; 
 int qtrue ; 
 int random () ; 
 TYPE_3__* replychats ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int BotReplyChat(int chatstate, char *message, int mcontext, int vcontext, char *var0, char *var1, char *var2, char *var3, char *var4, char *var5, char *var6, char *var7)
{
	bot_replychat_t *rchat, *bestrchat;
	bot_replychatkey_t *key;
	bot_chatmessage_t *m, *bestchatmessage;
	bot_match_t match, bestmatch;
	int bestpriority, num, found, res, numchatmessages, index;
	bot_chatstate_t *cs;

	cs = BotChatStateFromHandle(chatstate);
	if (!cs) return qfalse;
	Com_Memset(&match, 0, sizeof(bot_match_t));
	strcpy(match.string, message);
	bestpriority = -1;
	bestchatmessage = NULL;
	bestrchat = NULL;
	//go through all the reply chats
	for (rchat = replychats; rchat; rchat = rchat->next)
	{
		found = qfalse;
		for (key = rchat->keys; key; key = key->next)
		{
			res = qfalse;
			//get the match result
			if (key->flags & RCKFL_NAME) res = (StringContains(message, cs->name, qfalse) != -1);
			else if (key->flags & RCKFL_BOTNAMES) res = (StringContains(key->string, cs->name, qfalse) != -1);
			else if (key->flags & RCKFL_GENDERFEMALE) res = (cs->gender == CHAT_GENDERFEMALE);
			else if (key->flags & RCKFL_GENDERMALE) res = (cs->gender == CHAT_GENDERMALE);
			else if (key->flags & RCKFL_GENDERLESS) res = (cs->gender == CHAT_GENDERLESS);
			else if (key->flags & RCKFL_VARIABLES) res = StringsMatch(key->match, &match);
			else if (key->flags & RCKFL_STRING) res = (StringContainsWord(message, key->string, qfalse) != NULL);
			//if the key must be present
			if (key->flags & RCKFL_AND)
			{
				if (!res)
				{
					found = qfalse;
					break;
				} //end if
			} //end else if
			//if the key must be absent
			else if (key->flags & RCKFL_NOT)
			{
				if (res)
				{
					found = qfalse;
					break;
				} //end if
			} //end if
			else if (res)
			{
				found = qtrue;
			} //end else
		} //end for
		//
		if (found)
		{
			if (rchat->priority > bestpriority)
			{
				numchatmessages = 0;
				for (m = rchat->firstchatmessage; m; m = m->next)
				{
					if (m->time > AAS_Time()) continue;
					numchatmessages++;
				} //end if
				num = random() * numchatmessages;
				for (m = rchat->firstchatmessage; m; m = m->next)
				{
					if (--num < 0) break;
					if (m->time > AAS_Time()) continue;
				} //end for
				//if the reply chat has a message
				if (m)
				{
					Com_Memcpy(&bestmatch, &match, sizeof(bot_match_t));
					bestchatmessage = m;
					bestrchat = rchat;
					bestpriority = rchat->priority;
				} //end if
			} //end if
		} //end if
	} //end for
	if (bestchatmessage)
	{
		index = strlen(bestmatch.string);
		if( var0 ) {
			strcat(bestmatch.string, var0);
			bestmatch.variables[0].offset = index;
			bestmatch.variables[0].length = strlen(var0);
			index += strlen(var0);
		}
		if( var1 ) {
			strcat(bestmatch.string, var1);
			bestmatch.variables[1].offset = index;
			bestmatch.variables[1].length = strlen(var1);
			index += strlen(var1);
		}
		if( var2 ) {
			strcat(bestmatch.string, var2);
			bestmatch.variables[2].offset = index;
			bestmatch.variables[2].length = strlen(var2);
			index += strlen(var2);
		}
		if( var3 ) {
			strcat(bestmatch.string, var3);
			bestmatch.variables[3].offset = index;
			bestmatch.variables[3].length = strlen(var3);
			index += strlen(var3);
		}
		if( var4 ) {
			strcat(bestmatch.string, var4);
			bestmatch.variables[4].offset = index;
			bestmatch.variables[4].length = strlen(var4);
			index += strlen(var4);
		}
		if( var5 ) {
			strcat(bestmatch.string, var5);
			bestmatch.variables[5].offset = index;
			bestmatch.variables[5].length = strlen(var5);
			index += strlen(var5);
		}
		if( var6 ) {
			strcat(bestmatch.string, var6);
			bestmatch.variables[6].offset = index;
			bestmatch.variables[6].length = strlen(var6);
			index += strlen(var6);
		}
		if( var7 ) {
			strcat(bestmatch.string, var7);
			bestmatch.variables[7].offset = index;
			bestmatch.variables[7].length = strlen(var7);
		}
		if (LibVarGetValue("bot_testrchat"))
		{
			for (m = bestrchat->firstchatmessage; m; m = m->next)
			{
				BotConstructChatMessage(cs, m->chatmessage, mcontext, &bestmatch, vcontext, qtrue);
				BotRemoveTildes(cs->chatmessage);
				botimport.Print(PRT_MESSAGE, "%s\n", cs->chatmessage);
			} //end if
		} //end if
		else
		{
			bestchatmessage->time = AAS_Time() + CHATMESSAGE_RECENTTIME;
			BotConstructChatMessage(cs, bestchatmessage->chatmessage, mcontext, &bestmatch, vcontext, qtrue);
		} //end else
		return qtrue;
	} //end if
	return qfalse;
}
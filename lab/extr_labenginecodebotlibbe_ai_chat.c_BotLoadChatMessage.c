#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ type; char* string; int subtype; char* intvalue; } ;
typedef  TYPE_1__ token_t ;
typedef  int /*<<< orphan*/  source_t ;

/* Variables and functions */
 int ESCAPE_CHAR ; 
 int MAX_MESSAGE_SIZE ; 
 scalar_t__ PC_CheckTokenString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PC_ExpectAnyToken (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  PC_ExpectTokenString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SourceError (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  StripDoubleQuotes (char*) ; 
 int TT_INTEGER ; 
 scalar_t__ TT_NAME ; 
 scalar_t__ TT_NUMBER ; 
 scalar_t__ TT_STRING ; 
 int qfalse ; 
 int qtrue ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 size_t strlen (char*) ; 

int BotLoadChatMessage(source_t *source, char *chatmessagestring)
{
	char *ptr;
	token_t token;

	ptr = chatmessagestring;
	*ptr = 0;
	//
	while(1)
	{
		if (!PC_ExpectAnyToken(source, &token)) return qfalse;
		//fixed string
		if (token.type == TT_STRING)
		{
			StripDoubleQuotes(token.string);
			if (strlen(ptr) + strlen(token.string) + 1 > MAX_MESSAGE_SIZE)
			{
				SourceError(source, "chat message too long");
				return qfalse;
			} //end if
			strcat(ptr, token.string);
		} //end else if
		//variable string
		else if (token.type == TT_NUMBER && (token.subtype & TT_INTEGER))
		{
			if (strlen(ptr) + 7 > MAX_MESSAGE_SIZE)
			{
				SourceError(source, "chat message too long");
				return qfalse;
			} //end if
			sprintf(&ptr[strlen(ptr)], "%cv%ld%c", ESCAPE_CHAR, token.intvalue, ESCAPE_CHAR);
		} //end if
		//random string
		else if (token.type == TT_NAME)
		{
			if (strlen(ptr) + 7 > MAX_MESSAGE_SIZE)
			{
				SourceError(source, "chat message too long");
				return qfalse;
			} //end if
			sprintf(&ptr[strlen(ptr)], "%cr%s%c", ESCAPE_CHAR, token.string, ESCAPE_CHAR);
		} //end else if
		else
		{
			SourceError(source, "unknown message component %s", token.string);
			return qfalse;
		} //end else
		if (PC_CheckTokenString(source, ";")) break;
		if (!PC_ExpectTokenString(source, ",")) return qfalse;
	} //end while
	//
	return qtrue;
}
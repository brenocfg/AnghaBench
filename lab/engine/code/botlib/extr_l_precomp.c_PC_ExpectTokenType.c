#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int type; int subtype; int /*<<< orphan*/  string; } ;
typedef  TYPE_1__ token_t ;
typedef  int /*<<< orphan*/  source_t ;

/* Variables and functions */
 int MAX_TOKEN ; 
 int /*<<< orphan*/  PC_ReadToken (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  SourceError (int /*<<< orphan*/ *,char*,...) ; 
 int TT_BINARY ; 
 int TT_DECIMAL ; 
 int TT_FLOAT ; 
 int TT_HEX ; 
 int TT_INTEGER ; 
 int TT_LITERAL ; 
 int TT_LONG ; 
 int TT_NAME ; 
 int TT_NUMBER ; 
 int TT_OCTAL ; 
 int TT_PUNCTUATION ; 
 int TT_STRING ; 
 int TT_UNSIGNED ; 
 int qfalse ; 
 int qtrue ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

int PC_ExpectTokenType(source_t *source, int type, int subtype, token_t *token)
{
	char str[MAX_TOKEN];

	if (!PC_ReadToken(source, token))
	{
		SourceError(source, "couldn't read expected token");
		return qfalse;
	} //end if

	if (token->type != type)
	{
		strcpy(str, "");
		if (type == TT_STRING) strcpy(str, "string");
		if (type == TT_LITERAL) strcpy(str, "literal");
		if (type == TT_NUMBER) strcpy(str, "number");
		if (type == TT_NAME) strcpy(str, "name");
		if (type == TT_PUNCTUATION) strcpy(str, "punctuation");
		SourceError(source, "expected a %s, found %s", str, token->string);
		return qfalse;
	} //end if
	if (token->type == TT_NUMBER)
	{
		if ((token->subtype & subtype) != subtype)
		{
			strcpy(str, "");
			if (subtype & TT_DECIMAL) strcpy(str, "decimal");
			if (subtype & TT_HEX) strcpy(str, "hex");
			if (subtype & TT_OCTAL) strcpy(str, "octal");
			if (subtype & TT_BINARY) strcpy(str, "binary");
			if (subtype & TT_LONG) strcat(str, " long");
			if (subtype & TT_UNSIGNED) strcat(str, " unsigned");
			if (subtype & TT_FLOAT) strcat(str, " float");
			if (subtype & TT_INTEGER) strcat(str, " integer");
			SourceError(source, "expected %s, found %s", str, token->string);
			return qfalse;
		} //end if
	} //end if
	else if (token->type == TT_PUNCTUATION)
	{
		if (token->subtype != subtype)
		{
			SourceError(source, "found %s", token->string);
			return qfalse;
		} //end if
	} //end else if
	return qtrue;
}
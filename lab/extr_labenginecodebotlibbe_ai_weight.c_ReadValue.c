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
struct TYPE_3__ {scalar_t__ type; float floatvalue; int /*<<< orphan*/  string; } ;
typedef  TYPE_1__ token_t ;
typedef  int /*<<< orphan*/  source_t ;

/* Variables and functions */
 int /*<<< orphan*/  PC_ExpectAnyToken (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  SourceError (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  SourceWarning (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ TT_NUMBER ; 
 int qfalse ; 
 int qtrue ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

int ReadValue(source_t *source, float *value)
{
	token_t token;

	if (!PC_ExpectAnyToken(source, &token)) return qfalse;
	if (!strcmp(token.string, "-"))
	{
		SourceWarning(source, "negative value set to zero");

		if(!PC_ExpectAnyToken(source, &token))
		{
			SourceError(source, "Missing return value");
			return qfalse;
		}
	}

	if (token.type != TT_NUMBER)
	{
		SourceError(source, "invalid return value %s", token.string);
		return qfalse;
	}
	
	*value = token.floatvalue;
	return qtrue;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int intvalue; int /*<<< orphan*/  string; } ;
typedef  TYPE_1__ token_t ;
typedef  int /*<<< orphan*/  source_t ;
struct TYPE_9__ {int index; int value; struct TYPE_9__* next; struct TYPE_9__* child; scalar_t__ weight; } ;
typedef  TYPE_2__ fuzzyseperator_t ;

/* Variables and functions */
 int /*<<< orphan*/  FreeFuzzySeperators_r (TYPE_2__*) ; 
 scalar_t__ GetClearedMemory (int) ; 
 void* MAX_INVENTORYVALUE ; 
 int /*<<< orphan*/  PC_ExpectAnyToken (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  PC_ExpectTokenString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PC_ExpectTokenType (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ReadFuzzyWeight (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  SourceError (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  SourceWarning (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  TT_INTEGER ; 
 int /*<<< orphan*/  TT_NUMBER ; 
 int qfalse ; 
 int qtrue ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

fuzzyseperator_t *ReadFuzzySeperators_r(source_t *source)
{
	int newindent, index, def, founddefault;
	token_t token;
	fuzzyseperator_t *fs, *lastfs, *firstfs;

	founddefault = qfalse;
	firstfs = NULL;
	lastfs = NULL;
	if (!PC_ExpectTokenString(source, "(")) return NULL;
	if (!PC_ExpectTokenType(source, TT_NUMBER, TT_INTEGER, &token)) return NULL;
	index = token.intvalue;
	if (!PC_ExpectTokenString(source, ")")) return NULL;
	if (!PC_ExpectTokenString(source, "{")) return NULL;
	if (!PC_ExpectAnyToken(source, &token)) return NULL;
	do
	{
		def = !strcmp(token.string, "default");
		if (def || !strcmp(token.string, "case"))
		{
			fs = (fuzzyseperator_t *) GetClearedMemory(sizeof(fuzzyseperator_t));
			fs->index = index;
			if (lastfs) lastfs->next = fs;
			else firstfs = fs;
			lastfs = fs;
			if (def)
			{
				if (founddefault)
				{
					SourceError(source, "switch already has a default");
					FreeFuzzySeperators_r(firstfs);
					return NULL;
				} //end if
				fs->value = MAX_INVENTORYVALUE;
				founddefault = qtrue;
			} //end if
			else
			{
				if (!PC_ExpectTokenType(source, TT_NUMBER, TT_INTEGER, &token))
				{
					FreeFuzzySeperators_r(firstfs);
					return NULL;
				} //end if
				fs->value = token.intvalue;
			} //end else
			if (!PC_ExpectTokenString(source, ":") || !PC_ExpectAnyToken(source, &token))
			{
				FreeFuzzySeperators_r(firstfs);
				return NULL;
			} //end if
			newindent = qfalse;
			if (!strcmp(token.string, "{"))
			{
				newindent = qtrue;
				if (!PC_ExpectAnyToken(source, &token))
				{
					FreeFuzzySeperators_r(firstfs);
					return NULL;
				} //end if
			} //end if
			if (!strcmp(token.string, "return"))
			{
				if (!ReadFuzzyWeight(source, fs))
				{
					FreeFuzzySeperators_r(firstfs);
					return NULL;
				} //end if
			} //end if
			else if (!strcmp(token.string, "switch"))
			{
				fs->child = ReadFuzzySeperators_r(source);
				if (!fs->child)
				{
					FreeFuzzySeperators_r(firstfs);
					return NULL;
				} //end if
			} //end else if
			else
			{
				SourceError(source, "invalid name %s", token.string);
				return NULL;
			} //end else
			if (newindent)
			{
				if (!PC_ExpectTokenString(source, "}"))
				{
					FreeFuzzySeperators_r(firstfs);
					return NULL;
				} //end if
			} //end if
		} //end if
		else
		{
			FreeFuzzySeperators_r(firstfs);
			SourceError(source, "invalid name %s", token.string);
			return NULL;
		} //end else
		if (!PC_ExpectAnyToken(source, &token))
		{
			FreeFuzzySeperators_r(firstfs);
			return NULL;
		} //end if
	} while(strcmp(token.string, "}"));
	//
	if (!founddefault)
	{
		SourceWarning(source, "switch without default");
		fs = (fuzzyseperator_t *) GetClearedMemory(sizeof(fuzzyseperator_t));
		fs->index = index;
		fs->value = MAX_INVENTORYVALUE;
		fs->weight = 0;
		fs->next = NULL;
		fs->child = NULL;
		if (lastfs) lastfs->next = fs;
		else firstfs = fs;
	} //end if
	//
	return firstfs;
}
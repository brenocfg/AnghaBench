#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  string; } ;
typedef  TYPE_1__ token_t ;
typedef  int /*<<< orphan*/  script_t ;
struct TYPE_8__ {void* value; void* key; } ;
typedef  TYPE_2__ epair_t ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* GetMemory (int) ; 
 int MAX_KEY ; 
 int MAX_VALUE ; 
 int /*<<< orphan*/  PS_ExpectAnyToken (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  StripDoubleQuotes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StripTrailing (void*) ; 
 void* copystring (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 

epair_t *ParseEpair(script_t *script)
{
	epair_t *e;
	token_t token;

	e = GetMemory(sizeof(epair_t));
	memset (e, 0, sizeof(epair_t));
	
	PS_ExpectAnyToken(script, &token);
	StripDoubleQuotes(token.string);
	if (strlen(token.string) >= MAX_KEY-1)
		Error ("ParseEpair: token %s too long", token.string);
	e->key = copystring(token.string);
	PS_ExpectAnyToken(script, &token);
	StripDoubleQuotes(token.string);
	if (strlen(token.string) >= MAX_VALUE-1)
		Error ("ParseEpair: token %s too long", token.string);
	e->value = copystring(token.string);

	// strip trailing spaces
	StripTrailing(e->key);
	StripTrailing(e->value);

	return e;
}
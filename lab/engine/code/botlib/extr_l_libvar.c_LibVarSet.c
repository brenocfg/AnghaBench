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
struct TYPE_4__ {char* string; int /*<<< orphan*/  modified; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ libvar_t ;

/* Variables and functions */
 int /*<<< orphan*/  FreeMemory (char*) ; 
 scalar_t__ GetMemory (scalar_t__) ; 
 TYPE_1__* LibVarAlloc (char const*) ; 
 TYPE_1__* LibVarGet (char const*) ; 
 int /*<<< orphan*/  LibVarStringValue (char*) ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

void LibVarSet(const char *var_name, const char *value)
{
	libvar_t *v;

	v = LibVarGet(var_name);
	if (v)
	{
		FreeMemory(v->string);
	} //end if
	else
	{
		v = LibVarAlloc(var_name);
	} //end else
	//variable string
	v->string = (char *) GetMemory(strlen(value) + 1);
	strcpy(v->string, value);
	//the value
	v->value = LibVarStringValue(v->string);
	//variable is modified
	v->modified = qtrue;
}
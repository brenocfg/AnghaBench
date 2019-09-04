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

/* Variables and functions */
 int MAX_CVAR_VALUE_STRING ; 
 int cmd_argc ; 
 char** cmd_argv ; 
 int strlen (char*) ; 
 char* strpbrk (char*,char*) ; 

void Cmd_Args_Sanitize(void)
{
	int i;

	for(i = 1; i < cmd_argc; i++)
	{
		char *c = cmd_argv[i];
		
		if(strlen(c) > MAX_CVAR_VALUE_STRING - 1)
			c[MAX_CVAR_VALUE_STRING - 1] = '\0';
		
		while ((c = strpbrk(c, "\n\r;"))) {
			*c = ' ';
			++c;
		}
	}
}
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
 char* yychars ; 
 int yypos ; 
 int* yytext ; 

__attribute__((used)) static char *yytexttochar()
{
	int i;

	for (i = 0; i < yypos; i++)
		yychars[i] = (char)(yytext[i] & 0xff);
	yychars[i] = '\0';
	return yychars;
}
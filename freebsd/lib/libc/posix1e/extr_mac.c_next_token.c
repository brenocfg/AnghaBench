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
 char* strsep (char**,char*) ; 

__attribute__((used)) static char *
next_token(char **string)
{
	char *token;

	token = strsep(string, " \t");
	while (token != NULL && *token == '\0')
		token = strsep(string, " \t");

	return (token);
}
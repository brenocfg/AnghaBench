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
 char* memmem (char const*,int,char const*,int) ; 
 char* strchrnul (char*,char) ; 
 int strlen (char const*) ; 

__attribute__((used)) static const char *find_encoding(const char *begin, const char *end)
{
	const char *needle = "\nencoding ";
	char *bol, *eol;

	bol = memmem(begin, end ? end - begin : strlen(begin),
		     needle, strlen(needle));
	if (!bol)
		return NULL;
	bol += strlen(needle);
	eol = strchrnul(bol, '\n');
	*eol = '\0';
	return bol;
}
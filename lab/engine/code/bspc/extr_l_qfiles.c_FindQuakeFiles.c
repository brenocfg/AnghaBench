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
typedef  int /*<<< orphan*/  quakefile_t ;

/* Variables and functions */
 int /*<<< orphan*/  ConvertPath (char*) ; 
 int /*<<< orphan*/ * FindQuakeFilesWithPakFilter (char*,char*) ; 
 int MAX_PATH ; 
 char* StringContains (char*,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

quakefile_t *FindQuakeFiles(char *filter)
{
	char *str;
	char newfilter[MAX_PATH];
	char pakfilter[MAX_PATH];
	char filefilter[MAX_PATH];

	strcpy(newfilter, filter);
	ConvertPath(newfilter);
	strcpy(pakfilter, newfilter);

	str = StringContains(pakfilter, ".pak", false);
	if (!str) str = StringContains(pakfilter, ".pk3", false);

	if (str)
	{
		str += strlen(".pak");
		if (*str)
		{
			*str++ = '\0';
			while(*str == '\\' || *str == '/') str++;
			strcpy(filefilter, str);
			return FindQuakeFilesWithPakFilter(pakfilter, filefilter);
		} //end if
	} //end else
	return FindQuakeFilesWithPakFilter(NULL, newfilter);
}
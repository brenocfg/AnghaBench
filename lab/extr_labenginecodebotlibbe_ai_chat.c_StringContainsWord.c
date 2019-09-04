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
 int strlen (char*) ; 
 scalar_t__ toupper (char) ; 

char *StringContainsWord(char *str1, char *str2, int casesensitive)
{
	int len, i, j;

	len = strlen(str1) - strlen(str2);
	for (i = 0; i <= len; i++, str1++)
	{
		//if not at the start of the string
		if (i)
		{
			//skip to the start of the next word
			while(*str1 && *str1 != ' ' && *str1 != '.' && *str1 != ',' && *str1 != '!') str1++;
			if (!*str1) break;
			str1++;
		} //end for
		//compare the word
		for (j = 0; str2[j]; j++)
		{
			if (casesensitive)
			{
				if (str1[j] != str2[j]) break;
			} //end if
			else
			{
				if (toupper(str1[j]) != toupper(str2[j])) break;
			} //end else
		} //end for
		//if there was a word match
		if (!str2[j])
		{
			//if the first string has an end of word
			if (!str1[j] || str1[j] == ' ' || str1[j] == '.' || str1[j] == ',' || str1[j] == '!') return str1;
		} //end if
	} //end for
	return NULL;
}
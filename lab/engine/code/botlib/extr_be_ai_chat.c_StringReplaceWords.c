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
 int /*<<< orphan*/  Com_Memcpy (char*,char*,int) ; 
 char* StringContainsWord (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int /*<<< orphan*/  qfalse ; 
 int strlen (char*) ; 

void StringReplaceWords(char *string, char *synonym, char *replacement)
{
	char *str, *str2;

	//find the synonym in the string
	str = StringContainsWord(string, synonym, qfalse);
	//if the synonym occurred in the string
	while(str)
	{
		//if the synonym isn't part of the replacement which is already in the string
		//useful for abbreviations
		str2 = StringContainsWord(string, replacement, qfalse);
		while(str2)
		{
			if (str2 <= str && str < str2 + strlen(replacement)) break;
			str2 = StringContainsWord(str2+1, replacement, qfalse);
		} //end while
		if (!str2)
		{
			memmove(str + strlen(replacement), str+strlen(synonym), strlen(str+strlen(synonym))+1);
			//append the synonum replacement
			Com_Memcpy(str, replacement, strlen(replacement));
		} //end if
		//find the next synonym in the string
		str = StringContainsWord(str+strlen(replacement), synonym, qfalse);
	} //end if
}
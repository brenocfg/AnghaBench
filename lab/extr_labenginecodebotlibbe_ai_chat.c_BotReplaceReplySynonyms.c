#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned long context; TYPE_1__* firstsynonym; struct TYPE_6__* next; } ;
typedef  TYPE_2__ bot_synonymlist_t ;
struct TYPE_7__ {char* string; struct TYPE_7__* next; } ;
typedef  TYPE_3__ bot_synonym_t ;
struct TYPE_5__ {char* string; TYPE_3__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Memcpy (char*,char*,int) ; 
 char* StringContainsWord (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int /*<<< orphan*/  qfalse ; 
 int strlen (char*) ; 
 TYPE_2__* synonyms ; 

void BotReplaceReplySynonyms(char *string, unsigned long int context)
{
	char *str1, *str2, *replacement;
	bot_synonymlist_t *syn;
	bot_synonym_t *synonym;

	for (str1 = string; *str1; )
	{
		//go to the start of the next word
		while(*str1 && *str1 <= ' ') str1++;
		if (!*str1) break;
		//
		for (syn = synonyms; syn; syn = syn->next)
		{
			if (!(syn->context & context)) continue;
			for (synonym = syn->firstsynonym->next; synonym; synonym = synonym->next)
			{
				//if the synonym is not at the front of the string continue
				str2 = StringContainsWord(str1, synonym->string, qfalse);
				if (!str2 || str2 != str1) continue;
				//
				replacement = syn->firstsynonym->string;
				//if the replacement IS in front of the string continue
				str2 = StringContainsWord(str1, replacement, qfalse);
				if (str2 && str2 == str1) continue;
				//
				memmove(str1 + strlen(replacement), str1+strlen(synonym->string),
							strlen(str1+strlen(synonym->string)) + 1);
				//append the synonum replacement
				Com_Memcpy(str1, replacement, strlen(replacement));
				//
				break;
			} //end for
			//if a synonym has been replaced
			if (synonym) break;
		} //end for
		//skip over this word
		while(*str1 && *str1 > ' ') str1++;
		if (!*str1) break;
	} //end while
}
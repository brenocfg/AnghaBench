#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long context; float totalweight; TYPE_2__* firstsynonym; struct TYPE_4__* next; } ;
typedef  TYPE_1__ bot_synonymlist_t ;
struct TYPE_5__ {int /*<<< orphan*/  string; struct TYPE_5__* next; scalar_t__ weight; } ;
typedef  TYPE_2__ bot_synonym_t ;

/* Variables and functions */
 int /*<<< orphan*/  StringReplaceWords (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float random () ; 
 TYPE_1__* synonyms ; 

void BotReplaceWeightedSynonyms(char *string, unsigned long int context)
{
	bot_synonymlist_t *syn;
	bot_synonym_t *synonym, *replacement;
	float weight, curweight;

	for (syn = synonyms; syn; syn = syn->next)
	{
		if (!(syn->context & context)) continue;
		//choose a weighted random replacement synonym
		weight = random() * syn->totalweight;
		if (!weight) continue;
		curweight = 0;
		for (replacement = syn->firstsynonym; replacement; replacement = replacement->next)
		{
			curweight += replacement->weight;
			if (weight < curweight) break;
		} //end for
		if (!replacement) continue;
		//replace all synonyms with the replacement
		for (synonym = syn->firstsynonym; synonym; synonym = synonym->next)
		{
			if (synonym == replacement) continue;
			StringReplaceWords(string, synonym->string, replacement->string);
		} //end for
	} //end for
}
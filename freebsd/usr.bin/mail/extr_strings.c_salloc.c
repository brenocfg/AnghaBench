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
struct strings {char* s_topFree; int s_nleft; char* s_nextFree; } ;

/* Variables and functions */
 size_t NSPACE ; 
 int STRINGSIZE ; 
 int /*<<< orphan*/  err (int,char*,int) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 char* malloc (int) ; 
 struct strings* stringdope ; 

char *
salloc(int size)
{
	char *t;
	int s, index;
	struct strings *sp;

	s = size;
	s += (sizeof(char *) - 1);
	s &= ~(sizeof(char *) - 1);
	index = 0;
	for (sp = &stringdope[0]; sp < &stringdope[NSPACE]; sp++) {
		if (sp->s_topFree == NULL && (STRINGSIZE << index) >= s)
			break;
		if (sp->s_nleft >= s)
			break;
		index++;
	}
	if (sp >= &stringdope[NSPACE])
		errx(1, "String too large");
	if (sp->s_topFree == NULL) {
		index = sp - &stringdope[0];
		if ((sp->s_topFree = malloc(STRINGSIZE << index)) == NULL)
			err(1, "No room for space %d", index);
		sp->s_nextFree = sp->s_topFree;
		sp->s_nleft = STRINGSIZE << index;
	}
	sp->s_nleft -= s;
	t = sp->s_nextFree;
	sp->s_nextFree += s;
	return (t);
}
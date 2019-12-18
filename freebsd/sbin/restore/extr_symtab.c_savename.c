#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct strhdr {struct strhdr* next; } ;
struct TYPE_2__ {struct strhdr* next; } ;

/* Variables and functions */
 size_t STRTBLINCR ; 
 int /*<<< orphan*/  allocsize (size_t) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char*) ; 
 TYPE_1__* strtblhdr ; 

char *
savename(char *name)
{
	struct strhdr *np;
	size_t len;
	char *cp;

	if (name == NULL)
		panic("bad name\n");
	len = strlen(name);
	np = strtblhdr[len / STRTBLINCR].next;
	if (np != NULL) {
		strtblhdr[len / STRTBLINCR].next = np->next;
		cp = (char *)np;
	} else {
		cp = malloc(allocsize(len));
		if (cp == NULL)
			panic("no space for string table\n");
	}
	(void) strcpy(cp, name);
	return (cp);
}
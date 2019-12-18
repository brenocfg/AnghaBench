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
struct strhdr {struct strhdr* next; } ;

/* Variables and functions */
 size_t STRTBLINCR ; 
 size_t strlen (char*) ; 
 struct strhdr* strtblhdr ; 

void
freename(char *name)
{
	struct strhdr *tp, *np;

	tp = &strtblhdr[strlen(name) / STRTBLINCR];
	np = (struct strhdr *)name;
	np->next = tp->next;
	tp->next = np;
}
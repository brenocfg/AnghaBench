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
struct wordent {char* word; struct wordent* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  xprintf (char*,char*) ; 
 int /*<<< orphan*/  xputchar (char) ; 

void
prlex(struct wordent *sp0)
{
    struct wordent *sp = sp0->next;

    for (;;) {
	xprintf("%S", sp->word);
	sp = sp->next;
	if (sp == sp0)
	    break;
	if (sp->word[0] != '\n')
	    xputchar(' ');
    }
}
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
struct wordent {struct wordent* next; int /*<<< orphan*/ * word; } ;

/* Variables and functions */
 int /*<<< orphan*/  any (char*,int /*<<< orphan*/ ) ; 
 int asyn0 (struct wordent*,struct wordent*) ; 

__attribute__((used)) static int
asyntax(struct wordent *p1, struct wordent *p2)
{
    while (p1 != p2) {
	if (!any(";&\n", p1->word[0]))
	    return asyn0(p1, p2);
	p1 = p1->next;
    }
    return 0;
}
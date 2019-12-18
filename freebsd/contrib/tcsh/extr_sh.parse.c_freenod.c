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
struct wordent {struct wordent* prev; struct wordent* next; struct wordent* word; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfree (struct wordent*) ; 

__attribute__((used)) static struct wordent *
freenod(struct wordent *p1, struct wordent *p2)
{
    struct wordent *retp = p1->prev;

    while (p1 != p2) {
	xfree(p1->word);
	p1 = p1->next;
	xfree(p1->prev);
    }
    retp->next = p2;
    p2->prev = retp;
    return (retp);
}
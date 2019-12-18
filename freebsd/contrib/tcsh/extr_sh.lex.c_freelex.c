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
struct wordent {struct wordent* prev; struct wordent* word; struct wordent* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfree (struct wordent*) ; 

void
freelex(struct wordent *vp)
{
    struct wordent *fp;

    while (vp->next != vp) {
	fp = vp->next;
	vp->next = fp->next;
	xfree(fp->word);
	xfree(fp);
    }
    vp->prev = vp;
}
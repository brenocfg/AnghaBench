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
struct Hist {struct Hist* Hprev; struct Hist* Hnext; } ;

/* Variables and functions */
 int /*<<< orphan*/  histCount ; 
 struct Hist* histTail ; 

__attribute__((used)) static void
hinsert(struct Hist *hp, struct Hist *pp)
{
    struct Hist *fp = pp->Hnext;        /* following element, if any */
    hp->Hnext = fp, hp->Hprev = pp;
    pp->Hnext = hp;
    if (fp)
        fp->Hprev = hp;
    else
        histTail = hp;                  /* meaning hp->Hnext == NULL */
    histCount++;
}
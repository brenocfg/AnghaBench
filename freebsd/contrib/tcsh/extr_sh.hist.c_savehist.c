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
struct wordent {TYPE_1__* next; } ;
struct TYPE_2__ {char* word; } ;

/* Variables and functions */
 int /*<<< orphan*/  discardExcess (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enthist (int /*<<< orphan*/ ,struct wordent*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eventno ; 
 int /*<<< orphan*/  histlen ; 

void
savehist(
  struct wordent *sp,
  int mflg)				/* true if -m (merge) specified */
{
    /* throw away null lines */
    if (sp && sp->next->word[0] == '\n')
	return;
    if (sp)
        (void) enthist(++eventno, sp, 1, mflg, histlen);
    discardExcess(histlen);
}
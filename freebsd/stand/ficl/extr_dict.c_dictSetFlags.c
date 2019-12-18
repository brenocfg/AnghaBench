#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UNS8 ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {TYPE_3__* smudge; } ;
typedef  TYPE_1__ FICL_DICT ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_3__*) ; 

void dictSetFlags(FICL_DICT *pDict, UNS8 set, UNS8 clr)
{
    assert(pDict->smudge);
    pDict->smudge->flags |= set;
    pDict->smudge->flags &= ~clr;
    return;
}
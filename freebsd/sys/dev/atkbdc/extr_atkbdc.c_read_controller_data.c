#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  aux; int /*<<< orphan*/  kbd; } ;
typedef  int /*<<< orphan*/  KBDC ;

/* Variables and functions */
 scalar_t__ availq (int /*<<< orphan*/ *) ; 
 TYPE_1__* kbdcp (int /*<<< orphan*/ ) ; 
 int read_data (TYPE_1__*) ; 
 int removeq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_data (TYPE_1__*) ; 

int
read_controller_data(KBDC p)
{
    if (availq(&kbdcp(p)->kbd)) 
        return removeq(&kbdcp(p)->kbd);
    if (availq(&kbdcp(p)->aux)) 
        return removeq(&kbdcp(p)->aux);
    if (!wait_for_data(kbdcp(p)))
        return -1;		/* timeout */
    return read_data(kbdcp(p));
}
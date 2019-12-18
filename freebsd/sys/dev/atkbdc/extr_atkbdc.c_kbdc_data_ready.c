#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  aux; int /*<<< orphan*/  kbd; } ;
typedef  int /*<<< orphan*/  KBDC ;

/* Variables and functions */
 int KBDS_ANY_BUFFER_FULL ; 
 scalar_t__ availq (int /*<<< orphan*/ *) ; 
 TYPE_1__* kbdcp (int /*<<< orphan*/ ) ; 
 int read_status (TYPE_1__*) ; 

int
kbdc_data_ready(KBDC p)
{
    return (availq(&kbdcp(p)->kbd) || availq(&kbdcp(p)->aux) 
	|| (read_status(kbdcp(p)) & KBDS_ANY_BUFFER_FULL));
}
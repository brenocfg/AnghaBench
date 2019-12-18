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
struct TYPE_2__ {int command_mask; } ;
typedef  int /*<<< orphan*/  KBDC ;

/* Variables and functions */
 TYPE_1__* kbdcp (int /*<<< orphan*/ ) ; 

int
kbdc_get_device_mask(KBDC p)
{
    return kbdcp(p)->command_mask;
}
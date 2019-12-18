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
struct TYPE_3__ {scalar_t__ mark; scalar_t__ consume; } ;
typedef  TYPE_1__ Ring ;

/* Variables and functions */

int
ring_at_mark(Ring *ring)
{
    if (ring->mark == ring->consume) {
	return 1;
    } else {
	return 0;
    }
}
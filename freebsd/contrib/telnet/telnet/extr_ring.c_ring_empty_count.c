#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int size; int /*<<< orphan*/  supply; int /*<<< orphan*/  consume; } ;
typedef  TYPE_1__ Ring ;

/* Variables and functions */
 scalar_t__ ring_empty (TYPE_1__*) ; 
 int ring_subtract (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ring_empty_count(Ring *ring)
{
    if (ring_empty(ring)) {	/* if empty */
	    return ring->size;
    } else {
	return ring_subtract(ring, ring->consume, ring->supply);
    }
}
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
struct TYPE_5__ {int /*<<< orphan*/  supply; } ;
typedef  TYPE_1__ Ring ;

/* Variables and functions */
 int MIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  ring_empty_consecutive (TYPE_1__*) ; 
 int /*<<< orphan*/  ring_supplied (TYPE_1__*,int) ; 

void
ring_supply_data(Ring *ring, unsigned char *buffer, int count)
{
    int i;

    while (count) {
	i = MIN(count, ring_empty_consecutive(ring));
	memcpy(ring->supply, buffer, i);
	ring_supplied(ring, i);
	count -= i;
	buffer += i;
    }
}
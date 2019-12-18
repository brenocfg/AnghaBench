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
struct TYPE_3__ {int size; unsigned char* supply; unsigned char* consume; unsigned char* bottom; unsigned char* top; scalar_t__ clearto; } ;
typedef  TYPE_1__ Ring ;

/* Variables and functions */
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

int
ring_init(Ring *ring, unsigned char *buffer, int count)
{
    memset((char *)ring, 0, sizeof *ring);

    ring->size = count;

    ring->supply = ring->consume = ring->bottom = buffer;

    ring->top = ring->bottom+ring->size;

#ifdef	ENCRYPTION
    ring->clearto = 0;
#endif	/* ENCRYPTION */

    return 1;
}
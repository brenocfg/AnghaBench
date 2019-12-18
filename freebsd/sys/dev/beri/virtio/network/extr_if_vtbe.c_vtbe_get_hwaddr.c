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
typedef  char uint8_t ;
struct vtbe_softc {int dummy; } ;

/* Variables and functions */
 int arc4random () ; 

__attribute__((used)) static int
vtbe_get_hwaddr(struct vtbe_softc *sc, uint8_t *hwaddr)
{
	int rnd;

	/*
	 * Generate MAC address, use 'bsd' + random 24 low-order bits.
	 */

	rnd = arc4random() & 0x00ffffff;

	hwaddr[0] = 'b';
	hwaddr[1] = 's';
	hwaddr[2] = 'd';
	hwaddr[3] = rnd >> 16;
	hwaddr[4] = rnd >>  8;
	hwaddr[5] = rnd >>  0;

	return (0);
}
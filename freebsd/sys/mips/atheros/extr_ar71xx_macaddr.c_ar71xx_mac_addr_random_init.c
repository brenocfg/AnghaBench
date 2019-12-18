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
typedef  int uint32_t ;

/* Variables and functions */
 int arc4random () ; 

int
ar71xx_mac_addr_random_init(unsigned char *dst)
{
	uint32_t rnd;

	rnd = arc4random();

	dst[0] = 'b';
	dst[1] = 's';
	dst[2] = 'd';
	dst[3] = (rnd >> 24) & 0xff;
	dst[4] = (rnd >> 16) & 0xff;
	dst[5] = (rnd >> 8) & 0xff;

	return (0);
}
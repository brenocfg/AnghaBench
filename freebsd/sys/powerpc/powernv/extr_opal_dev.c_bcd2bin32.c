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

/* Variables and functions */
 int bcd2bin (int) ; 

__attribute__((used)) static int
bcd2bin32(int bcd)
{
	int out = 0;

	out += bcd2bin(bcd & 0xff);
	out += 100*bcd2bin((bcd & 0x0000ff00) >> 8);
	out += 10000*bcd2bin((bcd & 0x00ff0000) >> 16);
	out += 1000000*bcd2bin((bcd & 0xffff0000) >> 24);

	return (out);
}
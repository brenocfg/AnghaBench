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

__attribute__((used)) static int valid_cw(int cw)
{
	return (cw == 1 || cw == 3 || cw == 7 || cw == 15 || cw == 31 ||
		cw == 63 || cw == 127 || cw == 255 || cw == 511 || cw == 1023 ||
		cw == 2047 || cw == 4095 || cw == 8191 || cw == 16383 ||
		cw == 32767);
}
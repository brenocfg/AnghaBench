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
 int PERIPSIZE ; 

__attribute__((used)) static int
hashval(char *p, int len)
{
	int i, hv = 0xABC3D20F;

	for (i = 0; i < len; ++i, ++p)
		hv = (hv << 5) ^ (hv >> 23) ^ *p;
	hv = (hv ^ (hv >> 16)) & (PERIPSIZE - 1);
	return hv;
}
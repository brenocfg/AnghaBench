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

__attribute__((used)) static __inline bool
ishangul(int l, int t)
{

	return ((l >= 0x84 && l <= 0xD3) &&
	    ((t >= 0x41 && t <= 0x7E) || (t >= 0x81 && t <= 0xFE)));
}
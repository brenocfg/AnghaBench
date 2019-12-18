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
 int SCRH ; 
 int SCRW ; 
 int* vid ; 

__attribute__((used)) static __inline int
gpset(int x, int y, int val)
{
	if (x < 0 || y < 0 || SCRW <= x || SCRH <= y) {
		return 0;
	}
	vid[x + y * SCRW] = val;
	return 1;
}
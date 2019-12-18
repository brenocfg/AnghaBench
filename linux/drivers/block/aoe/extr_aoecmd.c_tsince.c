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
typedef  int u32 ;

/* Variables and functions */
 int jiffies ; 
 int jiffies_to_usecs (int) ; 

__attribute__((used)) static int
tsince(u32 tag)
{
	int n;

	n = jiffies & 0xffff;
	n -= tag & 0xffff;
	if (n < 0)
		n += 1<<16;
	return jiffies_to_usecs(n + 1);
}
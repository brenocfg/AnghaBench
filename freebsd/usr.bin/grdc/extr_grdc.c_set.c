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
 int* disp ; 
 int mask ; 
 int* next ; 
 int* old ; 

__attribute__((used)) static void
set(int t, int n)
{
	int i, m;

	m = 7<<n;
	for(i=0; i<5; i++) {
		next[i] |= ((disp[t]>>(4-i)*3)&07)<<n;
		mask |= (next[i]^old[i])&m;
	}
	if(mask&m)
		mask |= m;
}
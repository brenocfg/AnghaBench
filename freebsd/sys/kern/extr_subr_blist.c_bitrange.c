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
typedef  int u_daddr_t ;

/* Variables and functions */
 int BLIST_BMAP_RADIX ; 

__attribute__((used)) static inline u_daddr_t
bitrange(int n, int count)
{

	return (((u_daddr_t)-1 << n) &
	    ((u_daddr_t)-1 >> (BLIST_BMAP_RADIX - (n + count))));
}
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
typedef  int daddr_t ;

/* Variables and functions */
 int BLIST_BMAP_RADIX ; 
 int BLIST_META_MASK ; 
 int BLIST_META_RADIX ; 

__attribute__((used)) static inline daddr_t
radix_to_skip(daddr_t radix)
{

	return (radix /
	    ((BLIST_BMAP_RADIX / BLIST_META_RADIX) * BLIST_META_MASK));
}
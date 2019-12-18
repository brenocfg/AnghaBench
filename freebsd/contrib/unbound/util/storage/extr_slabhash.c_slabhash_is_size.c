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
struct slabhash {size_t size; } ;

/* Variables and functions */
 size_t slabhash_get_size (struct slabhash*) ; 

int slabhash_is_size(struct slabhash* sl, size_t size, size_t slabs)
{
	/* divide by slabs and then multiply by the number of slabs,
	 * because if the size is not an even multiple of slabs, the
	 * uneven amount needs to be removed for comparison */
	if(!sl) return 0;
	if(sl->size != slabs) return 0;
	if(slabs == 0) return 0;
	if( (size/slabs)*slabs == slabhash_get_size(sl))
		return 1;
	return 0;
}
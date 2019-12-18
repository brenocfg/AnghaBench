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
struct ohash {int dummy; } ;

/* Variables and functions */
 void* ohash_next (struct ohash*,unsigned int*) ; 

void *
ohash_first(struct ohash *h, unsigned int *pos)
{
	*pos = 0;
	return ohash_next(h, pos);
}
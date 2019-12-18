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
typedef  int lba_t ;

/* Variables and functions */
 int ENOSPC ; 
 int image_set_size (int) ; 
 int max_capacity ; 
 int min_capacity ; 
 int secsz ; 

__attribute__((used)) static int
capacity_resize(lba_t end)
{
	lba_t min_capsz, max_capsz;

	min_capsz = (min_capacity + secsz - 1) / secsz;
	max_capsz = (max_capacity + secsz - 1) / secsz;

	if (max_capsz != 0 && end > max_capsz)
		return (ENOSPC);
	if (end >= min_capsz)
		return (0);

	return (image_set_size(min_capsz));
}
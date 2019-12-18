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
struct malloc_type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  malloc_type_zone_allocated (struct malloc_type*,unsigned long,int) ; 

void
malloc_type_allocated(struct malloc_type *mtp, unsigned long size)
{

	if (size > 0)
		malloc_type_zone_allocated(mtp, size, -1);
}
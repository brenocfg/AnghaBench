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
struct mem_region {scalar_t__ mr_start; scalar_t__ mr_size; } ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 

__attribute__((used)) static int
memr_overlap(struct mem_region *r1, struct mem_region *r2)
{
	if ((r1->mr_start + r1->mr_size) < r2->mr_start ||
	    (r2->mr_start + r2->mr_size) < r1->mr_start)
		return (FALSE);

	return (TRUE);
}
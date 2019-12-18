#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  size_t grant_ref_t ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int GTF_reading ; 
 int GTF_writing ; 
 TYPE_1__* shared ; 

int
gnttab_query_foreign_access(grant_ref_t ref)
{
	uint16_t nflags;

	nflags = shared[ref].flags;

	return (nflags & (GTF_reading|GTF_writing));
}
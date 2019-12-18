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
struct TYPE_2__ {int /*<<< orphan*/  (* FreeMemory ) (unsigned long*) ;} ;

/* Variables and functions */
 unsigned long MEM_ID ; 
 TYPE_1__ botimport ; 
 int /*<<< orphan*/  stub1 (unsigned long*) ; 

void FreeMemory(void *ptr)
{
	unsigned long int *memid;

	memid = (unsigned long int *) ((char *) ptr - sizeof(unsigned long int));

	if (*memid == MEM_ID)
	{
		botimport.FreeMemory(memid);
	} //end if
}
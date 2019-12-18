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
union overhead {scalar_t__ ov_magic; int ov_index; union overhead* ov_next; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 scalar_t__ MAGIC ; 
 union overhead** nextf ; 

void
__crt_free(void *cp)
{
	int size;
	union overhead *op;

  	if (cp == NULL)
  		return;
	op = (union overhead *)((caddr_t)cp - sizeof (union overhead));
	if (op->ov_magic != MAGIC)
		return;				/* sanity */
  	size = op->ov_index;
	op->ov_next = nextf[size];	/* also clobbers ov_magic */
  	nextf[size] = op;
}
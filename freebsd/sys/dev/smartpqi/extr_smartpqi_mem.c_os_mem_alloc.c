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
typedef  int /*<<< orphan*/  pqisrc_softstate_t ;

/* Variables and functions */
 int M_NOWAIT ; 
 int /*<<< orphan*/  M_SMARTPQI ; 
 int M_ZERO ; 
 void* malloc (unsigned long,int /*<<< orphan*/ ,int) ; 

void  *os_mem_alloc(pqisrc_softstate_t *softs, size_t size)
{
	void *addr  = NULL;

	/* DBG_FUNC("IN\n");  */

	addr = malloc((unsigned long)size, M_SMARTPQI,
			M_NOWAIT | M_ZERO);

/*	DBG_FUNC("OUT\n"); */

	return addr;
}